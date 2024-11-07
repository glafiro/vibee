#pragma once

#include <array>
#include <vector>

#include "Utils.h"
#include "DSPParameters.h"
#include "FilteredParameter.h"
#include "LPFilter.h"

#define DEFAULT_SR 44100.0f
#define DEFAULT_BUFFER_SIZE 1
#define MAX_DELAY_LENGTH 2500.0f
#define TWO_PI 6.28318530718f

template <typename T>
class RingBuffer
{
    int bufferSize;
    int mask;
    std::vector<T> buffer;

    int writePointer{ 0 };
    int readPointer{ 0 };

    void createBuffer(int size) {
        bufferSize = nearestPowerOfTwo(size);
        buffer.resize(bufferSize, static_cast<T>(0.0f));
        mask = bufferSize - 1;
    }

public:

    RingBuffer(int size) {
        createBuffer(size);
    }

    RingBuffer() {
        createBuffer(DEFAULT_BUFFER_SIZE);
    }

    void write(T value) {
        buffer[writePointer] = value;
        writePointer++;
        writePointer &= mask;
    }

    T readInt(int delaySize) {
        readPointer = writePointer - 1 - delaySize;
        readPointer &= mask;
        return buffer[readPointer];
    }

    T read(float delaySize) {
        float frac = delaySize - floor(delaySize);
        int idx = static_cast<int>(delaySize);

        T a = readInt(idx);
        T b = readInt(idx + 1);
        T c = readInt(idx + 2);

        T out = a * (1.0f - frac)  + b + c * frac;
        out -= ((a - b) - (b - c)) / 50.0;
        return out * 0.5f;
    }

    ~RingBuffer() {}

};

class Vibrato
{
	float sampleRate{ DEFAULT_SR };
    float invSampleRate{ 1.0f / DEFAULT_SR };
	int blockSize{ 0 };
	float nChannels{ 2.0f };

	FilteredParameter vibRateParam{};
	FilteredParameter vibDepthParam{};
	FilteredParameter fmRateParam{};
	FilteredParameter fmDepthParam{};
	FilteredParameter mix{};
	FilteredParameter cutoffParam{};

    float vibPhase{};
    float fmPhase{};

    RingBuffer<float> ringBufferL {
        static_cast<int>((lengthToSamples(sampleRate, MAX_DELAY_LENGTH)))
    };

    std::array<RingBuffer<float>, 2> ringBuffers = {
        RingBuffer<float>(lengthToSamples(sampleRate, MAX_DELAY_LENGTH)),
        RingBuffer<float>(lengthToSamples(sampleRate, MAX_DELAY_LENGTH))
    };

    LPFilter filterL, filterR;

public:

	void prepare(DSPParameters<float>& params);
	void update(DSPParameters<float>& params);
	void processBlock(float* const* inputBuffer, int numChannels, int numSamples);
};