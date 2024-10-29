#include "PluginProcessor.h"
#include "PluginEditor.h"

VibeeAudioProcessor::VibeeAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

VibeeAudioProcessor::~VibeeAudioProcessor()
{
}

const juce::String VibeeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VibeeAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VibeeAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VibeeAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VibeeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VibeeAudioProcessor::getNumPrograms()
{
    return 1;   
}

int VibeeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VibeeAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String VibeeAudioProcessor::getProgramName (int index)
{
    return {};
}

void VibeeAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void VibeeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void VibeeAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VibeeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VibeeAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
}

bool VibeeAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* VibeeAudioProcessor::createEditor()
{
    return new VibeeAudioProcessorEditor (*this);
}

void VibeeAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void VibeeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VibeeAudioProcessor();
}
