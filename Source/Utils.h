#pragma once

#include <JuceHeader.h>
#include <cmath>

template<typename T>
inline static void castParameter(AudioProcessorValueTreeState& apvts,
    const ParameterID& id, T& destination)
{
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
    jassert(destination);
    // parameter does not exist or wrong type
}

inline unsigned int nearestPowerOfTwo(int n) {
    return pow(2, ceil(log(n) / log(2)));
}

template<typename T>
inline T lerp(T a, T b, T t) {
    return a + t * (b - a);
}

template<typename T>
inline T limit(T val, T min, T max) {
    if (val > max) return max;
    if (val < min) return min;
    return val;
}


inline float linearToDb(float input) {
    return 20.0f * log10f(fabsf(input) + 0.000001f);
}

inline float dbToLinear(float input) {
    return powf(10.0f, input / 20.0f);
}

inline float sign(float x) {
    return x < 0.0f ? -1.0f : 1.0f;
}

// https://www.musicdsp.org/en/latest/Effects/104-variable-hardness-clipping-function.html

inline float fastatan(float x)
{
    return (x / (1.0f + 0.28f * (x * x)));
}

template<typename T>
T lengthToSamples(T sr, T n) noexcept {
    return sr * n * static_cast<T>(0.001);
}