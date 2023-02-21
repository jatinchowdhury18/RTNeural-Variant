#include "RTNeuralVariant.h"

RTNeuralVariant::RTNeuralVariant()
{
}

void RTNeuralVariant::addParameters (Parameters& params)
{
}

void RTNeuralVariant::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void RTNeuralVariant::processAudioBlock (AudioBuffer<float>& buffer)
{
}

AudioProcessorEditor* RTNeuralVariant::createEditor()
{
    return new GenericAudioProcessorEditor { *this };
}

// This creates new instances of the plugin
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RTNeuralVariant();
}
