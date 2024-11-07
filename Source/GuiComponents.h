#pragma once


#include <JuceHeader.h>
#include "APVTSParameter.h"
#include "LookAndFeel.h"
#include "Utils.h"

class Knob : public Component
{
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Knob);

    Label label;
    String labelText;
    int width, height;
    AudioProcessorValueTreeState& state;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attachment;
    Image& sheet;

public:
    Slider slider;
    Knob(IAPVTSParameter* param, int w, int h, AudioProcessorValueTreeState& apvts, Image& sheet);
    ~Knob();
    void resized() override;
    void paint(Graphics& g) override;
    void paintSprite(Graphics& g);
};
