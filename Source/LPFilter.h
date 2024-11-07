#pragma once
#include <cmath>

const float PI{ 3.1415926535f };

// adapted from: https://www.musicdsp.org/en/latest/Filters/38-lp-and-hp-filter.html

class LPFilter {
    float sampleRate;
    float freq;
    float res{ std::sqrt(2.0f)};
    float a1, a2, a3, b1, b2, c;
    float x1, x2;
    float y1, y2;

public:
    void prepare(float sr) {
        sampleRate = sr;
        a1 = a2 = a3 = b1 = b2 = c = 0.0f;
        x1 = x2 = 0.0f;
        y1 = y2 = 0.0f;
    }

    void setCutoff(float f) {
        c = 1.0f / tan(PI * f / sampleRate);

        a1 = 1.0f / (1.0f + res * c + c * c);
        a2 = 2.0f * a1;
        a3 = a1;
        b1 = 2.0f * (1.0f - c * c) * a1;
        b2 = (1.0f - res * c + c * c) * a1;
    }

    float process(float in) {
        x2 = x1;
        x1 = in;

        float out = a1 * in + a2 * x1 + a3 * x2 - b1 * y1 - b2 * y2;

        y2 = y1;
        y1 = out;

        return out;
    }
};
