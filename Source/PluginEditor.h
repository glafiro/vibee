#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class VibeeAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    VibeeAudioProcessorEditor (VibeeAudioProcessor&);
    ~VibeeAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    VibeeAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibeeAudioProcessorEditor)
};
