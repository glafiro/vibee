/*
  ==============================================================================

    Vibrato.h
    Created: 29 Oct 2024 1:28:00pm
    Author:  dglaf

  ==============================================================================
*/

#pragma once

#include "Utils.h"
#include "DSPParameters.h"
#include "FilteredParameter.h"

#define DEFAULT_SR 44100.0f

class Vibrato
{
	float sampleRate{ DEFAULT_SR };
	int blockSize{ 0 };
	float nChannels{ 2.0f };

	FilteredParameter vibRate{};
	FilteredParameter vibDepth{};
	FilteredParameter fmRate{};
	FilteredParameter fmDepth{};
	FilteredParameter mix{};
	bool isOn{ true };

public:

	void prepare(DSPParameters<float>& params);
	void update(DSPParameters<float>& params);
	void processBlock(float* const* inputBuffer, int numChannels, int numSamples);
	//float processSample(float sample);

};