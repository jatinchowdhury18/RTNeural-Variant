#include "PluginEditor.h"

PluginEditor::PluginEditor (RTNeuralVariant& plug)
    : juce::AudioProcessorEditor (plug),
      plugin (plug),
      params_view (plugin.getState(), plugin.getState().params)
{
    model_load_button.setButtonText ("Load Model!");
    model_load_button.onClick = [this]
    {
        file_chooser = std::make_shared<juce::FileChooser> ("Load New Model", juce::File {}, "*.json");
        file_chooser->launchAsync (juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::openMode,
                                   [this] (const juce::FileChooser& fc)
                                   {
                                       if (fc.getResults().isEmpty())
                                           return;
                                       plugin.loadNewModel (fc.getResult());
                                   });
    };

    model_name_label.setColour (juce::Label::textColourId, juce::Colours::white);
    model_name_label.setColour (juce::Label::backgroundColourId, juce::Colours::darkgrey);
    model_name_label.setJustificationType (juce::Justification::centred);
    model_name_label.setText ("Current model: " + plugin.getCurrentModelName(), juce::dontSendNotification);
    model_name_changed_callback = plugin.model_name_updated.connect ([this]
                                                                     { model_name_label.setText ("Current model: " + plugin.getCurrentModelName(), juce::sendNotification); });

    addAndMakeVisible (model_load_button);
    addAndMakeVisible (model_name_label);
    addAndMakeVisible (params_view);
    setSize (400, 400);
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void PluginEditor::resized()
{
    auto bounds = getLocalBounds();
    model_load_button.setBounds (bounds.removeFromTop (50).reduced (10, 5));
    model_name_label.setBounds (bounds.removeFromTop (50).reduced (10, 5));
    params_view.setBounds (bounds);
}
