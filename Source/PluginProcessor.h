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
    MIX,
    CUTOFF,
    PARAM_COUNT
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

    std::array<std::unique_ptr<IAPVTSParameter>, ParameterNames::PARAM_COUNT> apvtsParameters;
    AudioProcessorValueTreeState     apvts;

private:
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void initializeParameters();

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
