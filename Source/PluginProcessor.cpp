#include "PluginProcessor.h"
#include "PluginEditor.h"

VibeeAudioProcessor::VibeeAudioProcessor() : AudioProcessor (
    BusesProperties()
        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
    ),
    apvts(*this, nullptr, "Parameters", createParameterLayout()),
    vibrato()
{
    apvts.state.addListener(this);

    for (auto& param : apvtsParameters) {
        param->castParameter(apvts);
    }
}

VibeeAudioProcessor::~VibeeAudioProcessor()
{
    apvts.state.removeListener(this);
}

const juce::String VibeeAudioProcessor::getName() const
{
    return "Vibee";
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
    int nChannels = getTotalNumInputChannels();

    vibratoParameters.set("sampleRate", sampleRate);
    vibratoParameters.set("blockSize", samplesPerBlock);
    vibratoParameters.set("nChannels", nChannels);

    for (auto& param : apvtsParameters) {
        vibratoParameters.set(param->id.getParamID().toStdString(), param->getDefault());
    }

    vibrato.prepare(vibratoParameters);
}

void VibeeAudioProcessor::updateDSP()
{
    for (auto& param : apvtsParameters) {
        vibratoParameters.set(param->id.getParamID().toStdString(), param->get());
    }

    vibrato.update(vibratoParameters);
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

    bool expected = true;

    if (isNonRealtime() || parametersChanged.compare_exchange_strong(expected, false)) {
        updateDSP();
    }

    vibrato.processBlock(
        buffer.getArrayOfWritePointers(),
        buffer.getNumChannels(),
        buffer.getNumSamples()
    );

}

bool VibeeAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* VibeeAudioProcessor::createEditor()
{
    //return new GenericAudioProcessorEditor(*this);
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

AudioProcessorValueTreeState::ParameterLayout VibeeAudioProcessor::createParameterLayout()
{
    AudioProcessorValueTreeState::ParameterLayout layout;

    initializeParameters();

    layout.add(std::make_unique <AudioParameterFloat>(
        apvtsParameters[ParameterNames::VIB_RATE]->id,
        apvtsParameters[ParameterNames::VIB_RATE]->displayValue,
        NormalisableRange<float>{ 0.0f, 1.0f, 0.01f },
        apvtsParameters[ParameterNames::VIB_RATE]->getDefault()
    ));
    
    layout.add(std::make_unique <AudioParameterFloat>(
        apvtsParameters[ParameterNames::VIB_DEPTH]->id,
        apvtsParameters[ParameterNames::VIB_DEPTH]->displayValue,
        NormalisableRange<float>{ 0.0f, 100.0f, 0.01f },
        apvtsParameters[ParameterNames::VIB_DEPTH]->getDefault()
    ));
    
    layout.add(std::make_unique <AudioParameterFloat>(
        apvtsParameters[ParameterNames::FM_RATE]->id,
        apvtsParameters[ParameterNames::FM_RATE]->displayValue,
        NormalisableRange<float>{ 0.0f, 1.0f, 0.01f },
        apvtsParameters[ParameterNames::FM_RATE]->getDefault()
    ));
    
    layout.add(std::make_unique <AudioParameterFloat>(
        apvtsParameters[ParameterNames::FM_DEPTH]->id,
        apvtsParameters[ParameterNames::FM_DEPTH]->displayValue,
        NormalisableRange<float>{ 0.0f, 100.0f, 0.01f },
        apvtsParameters[ParameterNames::FM_DEPTH]->getDefault()
    ));
    
    layout.add(std::make_unique <AudioParameterFloat>(
        apvtsParameters[ParameterNames::MIX]->id,
        apvtsParameters[ParameterNames::MIX]->displayValue,
        NormalisableRange<float>{ 0.0f, 100.0f, 0.01f },
        apvtsParameters[ParameterNames::MIX]->getDefault()
    ));
    
    layout.add(std::make_unique <AudioParameterFloat>(
        apvtsParameters[ParameterNames::CUTOFF]->id,
        apvtsParameters[ParameterNames::CUTOFF]->displayValue,
        NormalisableRange<float>{ 20.0f, 20000.0f, 0.01f, 0.2f },
        apvtsParameters[ParameterNames::CUTOFF]->getDefault()
    ));


    return layout;
}

void VibeeAudioProcessor::initializeParameters() {
    apvtsParameters = {
        std::make_unique<APVTSParameterFloat>("vibRate",  "Rate",     0.0f),
        std::make_unique<APVTSParameterFloat>("vibDepth", "Depth",    0.0f),
        std::make_unique<APVTSParameterFloat>("fmRate",   "FM Rate",  0.0f),
        std::make_unique<APVTSParameterFloat>("fmDepth",  "FM Depth", 0.0f),
        std::make_unique<APVTSParameterFloat>("mix",      "Mix",      100.0f),
        std::make_unique<APVTSParameterFloat>("cutoff",   "Cutoff",   20000.0f)
    };
}