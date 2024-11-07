#pragma once
#include <cmath>

const float TWO_PI{ 6.2831853071795864f };

class LFO
{
    float phase{0.0f};
    float freq{ 0.0f };
    float inc;
    float sampleRate{44100.0f};

public:

    void reset(float sr, float offset=0.0f) {
        sampleRate = sr;
    }

    float sine(float p) {
        return std::sin(TWO_PI * phase);
    }

    float nextSample() {
		phase += inc;
		if (phase >= 1.0f) phase -= 1.0f;
		
		return sine(phase);
    }

    void setFrequency(float f) {
        freq = f;
        inc = f / sampleRate;
    }

    float updateAndGetNext(float f) {
        setFrequency(f);
        return nextSample();
    }

};