#include "RTNeuralVariant.h"
#include "PluginEditor.h"

RTNeuralVariant::RTNeuralVariant() = default;

void RTNeuralVariant::loadNewModel (const juce::File& model_file)
{
    try
    {
        const auto model_json = chowdsp::JSONUtils::fromFile (model_file);
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
}

void RTNeuralVariant::processAudioBlock (juce::AudioBuffer<float>& buffer)
{
    in_gain.setGainDecibels (state.params.in_gain->getCurrentValue());
    in_gain.process (buffer);

    // process model variant here

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
