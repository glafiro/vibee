#include "GuiComponents.h"


Knob::Knob(IAPVTSParameter* param, int w, int h, AudioProcessorValueTreeState& apvts, Image& img) :
    width(w), height(h), state(apvts), sheet(img)
{
    slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    slider.setBounds(0, 0, w, h);
    addAndMakeVisible(slider);

    label.setText(param->displayValue, NotificationType::dontSendNotification);
    label.setJustificationType(Justification::centred);
    label.setBorderSize(BorderSize<int>(0));
    label.attachToComponent(&slider, false);
    addAndMakeVisible(label);

    setLookAndFeel(KnobLookAndFeel::get());

    // Attach GUI component to AudioProcessorValueTreeState
    attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(
        state, param->id.getParamID(), slider
    );
}

Knob::~Knob() {}

void Knob::resized() {
    auto bounds = getLocalBounds();
    auto sliderHeight = bounds.getWidth();
    slider.setBounds(bounds.withHeight(sliderHeight));
    label.setBounds(0, sliderHeight * 0.8f, bounds.getWidth(), bounds.getHeight() - sliderHeight);
}

void Knob::paint(Graphics& g) {
    auto bounds = getLocalBounds();
    auto targetArea = bounds.withHeight(bounds.getWidth())
        .reduced(bounds.getWidth() * 0.2f);

    auto spriteSize = sheet.getHeight();
    int idx = slider.getNormalisableRange().convertTo0to1(slider.getValue()) * 126;
    Rectangle<int> imgBounds(0 + idx * spriteSize, 0, spriteSize, spriteSize);
    
    Image clippedImage = sheet.getClippedImage(imgBounds);
    g.drawImage(clippedImage, targetArea.toFloat());
}