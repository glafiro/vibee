#include "Vibrato.h"

void Vibrato::prepare(DSPParameters<float>& params) {
	sampleRate = params["sampleRate"];
	blockSize = params["blockSize"];
	nChannels = params["nChannels"];

	vibRate.prepare(sampleRate);
	vibDepth.prepare(sampleRate);
	fmRate.prepare(sampleRate);
	fmDepth.prepare(sampleRate);

	update(params);
}

void Vibrato::update(DSPParameters<float>& params) {
	vibRate.update(params["vibRate"]);
	vibDepth.update(params["vibDepth"] * 0.01f);
	fmRate.update(params["fmRate"]);
	fmDepth.update(params["fmDepth"] * 0.01f);
	mix.update(params["mix"] * 0.01f);
	isOn = params["isOn"];
}

void Vibrato::processBlock(float* const* inputBuffer, int numChannels, int numSamples) {
	for (int ch = 0; ch < numChannels; ++ch) {
		for (int s = 0; s < numSamples; ++s) {
			auto sample = inputBuffer[ch][s];
			inputBuffer[ch][s] = sample;
		}
	}
}