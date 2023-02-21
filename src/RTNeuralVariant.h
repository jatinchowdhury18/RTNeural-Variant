#pragma once

#include <pch.h>

class RTNeuralVariant : public chowdsp::PluginBase<RTNeuralVariant>
{
public:
    RTNeuralVariant();

    static void addParameters (Parameters& params);

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    void processAudioBlock (AudioBuffer<float>& buffer) override;

    AudioProcessorEditor* createEditor() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RTNeuralVariant)
};
