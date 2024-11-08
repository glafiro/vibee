#pragma once
#include <JuceHeader.h>

namespace Colors
{
    const Colour cream{ 244, 224, 194 };
}


class KnobLookAndFeel : public LookAndFeel_V4
{
    float rotaryStart, rotaryEnd;
    Font labelFont;

public:
    KnobLookAndFeel() {
        // Shorten the ends of the rotary slider
        float pi = MathConstants<float>::pi;
        rotaryStart = 1.25f * pi;
        rotaryEnd = 2.75f * pi;

        labelFont = Font(Typeface::createSystemTypefaceFor(BinaryData::coolvetica_otf, BinaryData::coolvetica_otfSize));
    }

    static KnobLookAndFeel* get() {
        static KnobLookAndFeel inst;
        return &inst;
    }

    void drawLabel(Graphics& g, Label& l) override {
        auto bounds = l.getLocalBounds();
        auto fontSize = bounds.getHeight() * 0.8f;
        g.setColour(Colors::cream);
        g.setFont(labelFont.withHeight(fontSize));
        g.drawText(l.getText(), bounds, Justification::centred, false);
    }

    void drawRotarySlider(Graphics& g, int x, int y, int w, int h, float pos, float startAngle, float endAngle, Slider& slider) override {

        slider.setRotaryParameters(rotaryStart, rotaryEnd, true);

        auto bounds = slider.getLocalBounds().reduced(w * 0.04f);
        auto center = Point{ bounds.getX() + bounds.getWidth() / 2, bounds.getY() + bounds.getWidth() / 2 };

        // outerRadius and innerRadius are used to draw the background arc.
        // valueRadius is used to draw the (filled) arc corresponding to the slider value.
        auto outerRadius = bounds.getWidth() / 2.0f;
        auto innerRadius = outerRadius - (w * 0.06f);
        auto valueRadius = (innerRadius + outerRadius) * 0.5f;
        
        auto toAngle = startAngle + pos * (endAngle - startAngle);

        // Draw background arc. We draw an inner and outer arc, then we connect them.
        Path bgArc;

        bgArc.addCentredArc(
            center.x, center.y, 
            outerRadius, outerRadius, 
            0.0f, 
            startAngle, endAngle, 
            true
        );

        bgArc.addCentredArc(
            center.x, center.y, 
            innerRadius, innerRadius, 
            0.0f, 
            endAngle, startAngle, 
            false
        );

        bgArc.closeSubPath();
        g.setColour(Colors::cream);
        g.strokePath(bgArc, PathStrokeType(1.0f));
    
        // Draw value arc
        Path valueArc;
        valueArc.addCentredArc(center.x,
            center.y,
            valueRadius,
            valueRadius,
            0.0f,
            startAngle,
            toAngle,
            true);

        g.setColour(Colors::cream);

        auto strokeType = PathStrokeType(
            outerRadius - innerRadius, PathStrokeType::mitered, PathStrokeType::butt);
        g.strokePath(valueArc, strokeType);

    }
};
