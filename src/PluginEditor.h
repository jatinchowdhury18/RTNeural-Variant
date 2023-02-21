#pragma once

#include "RTNeuralVariant.h"

class PluginEditor : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor (RTNeuralVariant& plugin);

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    RTNeuralVariant& plugin;

    chowdsp::ParametersView params_view;
    juce::TextButton model_load_button;
    std::shared_ptr<juce::FileChooser> file_chooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
