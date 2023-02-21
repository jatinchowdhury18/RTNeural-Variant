#pragma once

#include <pch.h>
#include "model_variant.hpp"

struct Params : chowdsp::ParamHolder
{
    Params()
    {
        add (in_gain, out_gain);
    }

    chowdsp::GainDBParameter::Ptr in_gain {
        juce::ParameterID { "in_gain", 100 },
        "Input Gain",
        juce::NormalisableRange { -30.0f, 30.0f },
        0.0f
    };

    chowdsp::GainDBParameter::Ptr out_gain {
        juce::ParameterID { "out_gain", 100 },
        "Output Gain",
        juce::NormalisableRange { -30.0f, 30.0f },
        0.0f
    };
};

using State = chowdsp::PluginStateImpl<Params>;

class RTNeuralVariant : public chowdsp::PluginBase<State>
{
public:
    RTNeuralVariant();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    void processAudioBlock (juce::AudioBuffer<float>& buffer) override;

    juce::AudioProcessorEditor* createEditor() override;

    void loadNewModel (const juce::File& model_file);

    [[nodiscard]] juce::String getCurrentModelName() const noexcept { return current_model_name; }
    chowdsp::Broadcaster<void()> model_name_updated;

private:
    chowdsp::Gain<float> in_gain, out_gain;
    chowdsp::FirstOrderHPF<float> dc_blocker;

    ModelVariantType models[2];
    std::atomic_int active_model_index { 0 };
    std::atomic_int swap_model_index { 0 };
    int inactive_model_index { 1 };

    juce::String current_model_name { "None" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RTNeuralVariant)
};
