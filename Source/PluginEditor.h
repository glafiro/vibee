#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GuiComponents.h"


class VibeeAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    VibeeAudioProcessorEditor (VibeeAudioProcessor&);
    ~VibeeAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibeeAudioProcessorEditor)
    
    int PLUGIN_SIZE;
    
    VibeeAudioProcessor& audioProcessor;

    Image bgImg;
    Image shadowImg;
    Image knobImg;

    Knob vibRateKnob { audioProcessor.apvtsParameters[VIB_RATE].get(),  audioProcessor.apvts, knobImg };
    Knob vibDepthKnob{ audioProcessor.apvtsParameters[VIB_DEPTH].get(), audioProcessor.apvts, knobImg };
    Knob fmRateKnob  { audioProcessor.apvtsParameters[FM_RATE].get(),   audioProcessor.apvts, knobImg };
    Knob fmDepthKnob { audioProcessor.apvtsParameters[FM_DEPTH].get(),  audioProcessor.apvts, knobImg };
    Knob mixKnob     { audioProcessor.apvtsParameters[MIX].get(),       audioProcessor.apvts, knobImg };
    Knob cutoffKnob  { audioProcessor.apvtsParameters[CUTOFF].get(),    audioProcessor.apvts, knobImg};
};
