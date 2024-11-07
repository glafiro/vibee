#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GuiComponents.h"

#define PLUGIN_SIZE 600

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
    
    VibeeAudioProcessor& audioProcessor;

    Image bgImg;
    Image shadowImg;
    Image knobImg;

    int knobLarge = PLUGIN_SIZE * 0.25f;
    int knobSmall = PLUGIN_SIZE * 0.15f;

    Knob vibRateKnob { apvtsParameters[VIB_RATE].get(),   knobLarge, knobLarge, audioProcessor.apvts, knobImg};
    Knob vibDepthKnob{ apvtsParameters[VIB_DEPTH].get(),  knobLarge, knobLarge, audioProcessor.apvts, knobImg};
    Knob fmRateKnob  { apvtsParameters[FM_RATE].get(),    knobLarge, knobLarge, audioProcessor.apvts, knobImg};
    Knob fmDepthKnob { apvtsParameters[FM_DEPTH].get(),   knobLarge, knobLarge, audioProcessor.apvts, knobImg};
    Knob mixKnob    { apvtsParameters[MIX].get(),        knobLarge, knobLarge, audioProcessor.apvts, knobImg};
    Knob cutoffKnob  { apvtsParameters[CUTOFF].get(),     knobLarge, knobLarge, audioProcessor.apvts, knobImg};
};
