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
    void paintOverChildren(juce::Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibeeAudioProcessorEditor)
    
    int PLUGIN_SIZE;
    
    VibeeAudioProcessor& audioProcessor;

    Image bgImg;
    Image shadowImg;
    Image knobImg;

    Knob vibRateKnob { apvtsParameters[VIB_RATE].get(),  audioProcessor.apvts, knobImg};
    Knob vibDepthKnob{ apvtsParameters[VIB_DEPTH].get(), audioProcessor.apvts, knobImg};
    Knob fmRateKnob  { apvtsParameters[FM_RATE].get(),   audioProcessor.apvts, knobImg};
    Knob fmDepthKnob { apvtsParameters[FM_DEPTH].get(),  audioProcessor.apvts, knobImg};
    Knob mixKnob    { apvtsParameters[MIX].get(),        audioProcessor.apvts, knobImg};
    Knob cutoffKnob  { apvtsParameters[CUTOFF].get(),    audioProcessor.apvts, knobImg};
};
