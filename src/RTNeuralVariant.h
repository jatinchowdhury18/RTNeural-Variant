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

private:
    chowdsp::Gain<float> in_gain, out_gain;
    chowdsp::FirstOrderHPF<float> dc_blocker;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RTNeuralVariant)
};
