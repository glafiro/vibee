#pragma once

#include <JuceHeader.h>

#include <array>
using std::array;

#include "DSPParameters.h"
#include "APVTSParameter.h"
#include "Vibrato.h"

enum ParameterNames {
    VIB_RATE, VIB_DEPTH,
    FM_RATE, FM_DEPTH,
    MIX, IS_ON,
    PARAM_COUNT
};

static std::array<std::unique_ptr<IAPVTSParameter>, ParameterNames::PARAM_COUNT> apvtsParameters{
    std::make_unique<APVTSParameterFloat>("vibRate",  "VIB. RATE",  0.0f),
    std::make_unique<APVTSParameterFloat>("vibDepth", "VIB. DEPTH", 0.0f),
    std::make_unique<APVTSParameterFloat>("fmRate",   "FM RATE",    0.0f),
    std::make_unique<APVTSParameterFloat>("fmDepth",  "FM DEPTH",   0.0f),
    std::make_unique<APVTSParameterFloat>("mix",      "MIX",        100.0f),
    std::make_unique<APVTSParameterBool> ("isOn",     "On",         true)
};


class VibeeAudioProcessor  : 
    public juce::AudioProcessor,
    public ValueTree::Listener
{
public:
    VibeeAudioProcessor();
    ~VibeeAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    AudioProcessorValueTreeState     apvts;

private:
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    // Manage parameter changes in a thread-safe way
    std::atomic<bool> parametersChanged{ false };
    void valueTreePropertyChanged(ValueTree&, const Identifier&) override {
        parametersChanged.store(true);
    }

    DSPParameters<float> vibratoParameters;
    void updateDSP();

    Vibrato vibrato;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibeeAudioProcessor)
};