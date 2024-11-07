#pragma once

#include <cmath>
#include <vector>

class LadderFilter {
public:


    LadderFilter(float sr) : fs(sampleRate) {
        reset();
    }

    void reset() {
        y1 = y2 = y3 = y4 = 0.0f;
        feedback = 0.0f;
    }

    void setCutoff(float cutoffFreq) {
        float fc = cutoffFreq / fs;
        g = 4.0f * fc;  // Adjust the coefficient for cutoff frequency
        if (g > 1.0f) g = 1.0f;  // Limit to Nyquist frequency
    }

    void setResonance(float resonance) {
        resonance = (resonance > 4.0f) ? 4.0f : resonance;
        feedback = resonance * (1.0f - 0.15f * g * g);
    }

    float processSample(float input) {
        // Feedback for resonance
        input -= feedback * y4;

        // Process through the four stages of the filter
        y1 = y1 + g * (tanh(input) - tanh(y1));
        y2 = y2 + g * (tanh(y1) - tanh(y2));
        y3 = y3 + g * (tanh(y2) - tanh(y3));
        y4 = y4 + g * (tanh(y3) - tanh(y4));

        return y4;
    }

private:
    float fs;
    float g;        // Coefficient for frequency cutoff
    float feedback; // Feedback factor for resonance
    float y1, y2, y3, y4; // Outputs of each filter stage
};

// Usage example:
// LadderFilter filter(44100.0f);
// filter.setCutoff(1000.0f);
// filter.setResonance(1.0f);
// float output = filter.processSample(inputSample);
