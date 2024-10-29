#include "PluginProcessor.h"
#include "PluginEditor.h"

VibeeAudioProcessorEditor::VibeeAudioProcessorEditor (VibeeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
}

VibeeAudioProcessorEditor::~VibeeAudioProcessorEditor()
{
}

void VibeeAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void VibeeAudioProcessorEditor::resized()
{
}
