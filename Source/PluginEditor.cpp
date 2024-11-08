#include "PluginProcessor.h"
#include "PluginEditor.h"

VibeeAudioProcessorEditor::VibeeAudioProcessorEditor (VibeeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    bgImg = ImageCache::getFromMemory(BinaryData::base_png, BinaryData::base_pngSize);
    shadowImg = ImageCache::getFromMemory(BinaryData::shadows_png, BinaryData::shadows_pngSize);
    knobImg = ImageCache::getFromMemory(BinaryData::spritesheet_png, BinaryData::spritesheet_pngSize);

    addAndMakeVisible(vibRateKnob);
    addAndMakeVisible(vibDepthKnob);
    addAndMakeVisible(fmRateKnob);
    addAndMakeVisible(fmDepthKnob);
    addAndMakeVisible(mixKnob);
    addAndMakeVisible(cutoffKnob);

    setSize (PLUGIN_SIZE, PLUGIN_SIZE);
    setResizable(true, true);

    setResizeLimits(200, 200, 1600, 1600);
    getConstrainer()->setFixedAspectRatio(1);
}

VibeeAudioProcessorEditor::~VibeeAudioProcessorEditor()
{
}

void VibeeAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImage(bgImg, getLocalBounds().toFloat());
    g.drawImage(shadowImg, getLocalBounds().toFloat());
}

void VibeeAudioProcessorEditor::paintOverChildren(juce::Graphics& g)
{

    vibRateKnob.repaint();
    vibDepthKnob.repaint();
}

void VibeeAudioProcessorEditor::resized()
{
    auto bounds = getBounds();
    auto x = bounds.getX();
    auto y = bounds.getY();
    auto width = bounds.getWidth();
    auto height = bounds.getHeight();

    int knobLarge = width * 0.25f;
    int knobSmall = width * 0.15f;

    vibRateKnob.setBounds(Rectangle<int>(
        static_cast<int>(x + width * 0.39f),
        static_cast<int>(y + height * 0.33f),
        knobLarge,
        knobLarge * 1.25f
    ));
    
    vibDepthKnob.setBounds(Rectangle<int>(
        static_cast<int>(x + width * 0.7f),
        static_cast<int>(y + height * 0.33f),
        knobLarge,
        knobLarge * 1.25f
    ));

    fmRateKnob.setBounds(Rectangle<int>(
        static_cast<int>(x + width * 0.39f),
        static_cast<int>(y + height * 0.67f),
        knobLarge,
        knobLarge * 1.25f
    ));
    
    fmDepthKnob.setBounds(Rectangle<int>(
        static_cast<int>(x + width * 0.7f),
        static_cast<int>(y + height * 0.67f),
        knobLarge,
        knobLarge * 1.25f
    ));
    
    mixKnob.setBounds(Rectangle<int>(
        static_cast<int>(x + width * 0.05f),
        static_cast<int>(y + height * 0.75f),
        knobSmall,
        knobSmall * 1.25f
    ));
    
    cutoffKnob.setBounds(Rectangle<int>(
        static_cast<int>(x + width * 0.22f),
        static_cast<int>(y + height * 0.57f),
        knobSmall,
        knobSmall * 1.25f
    ));
}
