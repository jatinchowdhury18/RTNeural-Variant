#include "RTNeuralVariant.h"
#include "PluginEditor.h"

RTNeuralVariant::RTNeuralVariant() = default;

void RTNeuralVariant::loadNewModel (const juce::File& model_file)
{
    // wait for previous swap to complete
    while (active_model_index.load() != swap_model_index.load())
        juce::Thread::sleep (10);

    try
    {
        const auto model_json = chowdsp::JSONUtils::fromFile (model_file);
        if (! custom_model_creator (model_json, models[inactive_model_index]))
            throw std::runtime_error ("Unable to identify a known model architecture!");

        std::visit (
            [&model_json] (auto&& custom_model)
            {
                using ModelType = std::decay_t<decltype (custom_model)>;
                if constexpr (! std::is_same_v<ModelType, NullModel>)
                {
                    custom_model.parseJson (model_json, true);
                    custom_model.reset();
                }
            },
            models[inactive_model_index]);

        inactive_model_index = swap_model_index.exchange (inactive_model_index);

        current_model_name = model_file.getFileName();
        model_name_updated();
    }
    catch (const std::exception& e)
    {
        juce::NativeMessageBox::showMessageBoxAsync (juce::AlertWindow::WarningIcon,
                                                     "Error loading model!",
                                                     e.what());
    }
}

void RTNeuralVariant::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const auto process_spec = juce::dsp::ProcessSpec { sampleRate, (uint32_t) samplesPerBlock, (uint32_t) getMainBusNumInputChannels() };
    in_gain.prepare (process_spec);
    out_gain.prepare (process_spec);

    dc_blocker.prepare (process_spec);
    dc_blocker.calcCoefs (15.0f, (float) sampleRate);

    for (auto& model : models)
    {
        std::visit (
            [] (auto&& custom_model)
            {
                using ModelType = std::decay_t<decltype (custom_model)>;
                if constexpr (! std::is_same_v<ModelType, NullModel>)
                    custom_model.reset();
            },
            model);
    }
}

void RTNeuralVariant::processAudioBlock (juce::AudioBuffer<float>& buffer)
{
    in_gain.setGainDecibels (state.params.in_gain->getCurrentValue() + 20.0f);
    in_gain.process (buffer);

    active_model_index.store (swap_model_index.load());
    std::visit (
        [&buffer] (auto&& custom_model)
        {
            using ModelType = std::decay_t<decltype (custom_model)>;
            if constexpr (ModelType::input_size == 1)
            {
                // sum to mono
                if (buffer.getNumChannels() > 1)
                    chowdsp::BufferMath::sumToMono (buffer, buffer);

                for (auto& sample : std::span { buffer.getWritePointer (0), (size_t) buffer.getNumSamples() })
                    sample = custom_model.forward (&sample);

                // split from mono
                for (int ch = 1; ch < buffer.getNumChannels(); ++ch)
                    chowdsp::BufferMath::copyBufferChannels (buffer, buffer, 0, ch);
            }
            else if constexpr (ModelType::input_size == 2)
            {
                if (buffer.getNumChannels() != 2)
                    return; // stereo only!

                alignas (xsimd::default_arch::alignment()) float input_data[xsimd::batch<float>::size] {};
                auto** buffer_data = buffer.getArrayOfWritePointers();
                for (int n = 0; n < buffer.getNumSamples(); ++n)
                {
                    // load up input array
                    input_data[0] = buffer_data[0][n];
                    input_data[1] = buffer_data[1][n];

                    custom_model.forward (input_data);

                    buffer_data[0][n] = custom_model.getOutputs()[0];
                    buffer_data[1][n] = custom_model.getOutputs()[1];
                }
            }
            else
            {
                buffer.applyGain (juce::Decibels::decibelsToGain (-20.0f));
            }
        },
        models[active_model_index.load()]);

    out_gain.setGainDecibels (state.params.out_gain->getCurrentValue());
    out_gain.process (buffer);

    dc_blocker.processBlock (buffer);
}

juce::AudioProcessorEditor* RTNeuralVariant::createEditor()
{
    return new PluginEditor { *this };
}

// This creates new instances of the plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RTNeuralVariant();
}
