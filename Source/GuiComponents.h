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
    AudioProcessorValueTreeState& state;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attachment;
    Image& sheet;
    Slider slider;

public:
    Knob(IAPVTSParameter* param, AudioProcessorValueTreeState& apvts, Image& sheet);
    ~Knob();
    void resized() override;
    void paint(Graphics& g) override;
};
