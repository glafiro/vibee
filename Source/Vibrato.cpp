#include "Vibrato.h"

void Vibrato::prepare(DSPParameters<float>& params) {
	sampleRate = params["sampleRate"];
	invSampleRate = 1.0f / sampleRate;
	blockSize = params["blockSize"];
	nChannels = params["nChannels"];

	vibRateParam.prepare(sampleRate);
	vibDepthParam.prepare(sampleRate);
	fmRateParam.prepare(sampleRate);
	fmDepthParam.prepare(sampleRate);
	mix.prepare(sampleRate);
	cutoffParam.prepare(sampleRate);
	
	filterL.prepare(sampleRate);
	filterR.prepare(sampleRate);

	update(params);

}

void Vibrato::update(DSPParameters<float>& params) {
	vibRateParam.update(params["vibRate"]);
	vibDepthParam.update(params["vibDepth"] * 0.01f);
	fmRateParam.update(params["fmRate"]);
	fmDepthParam.update(params["fmDepth"] * 0.01f);
	mix.update(params["mix"] * 0.01f);
	cutoffParam.update(params["cutoff"]);

	filterL.setCutoff(cutoffParam.read());
	filterR.setCutoff(cutoffParam.read());

}

void Vibrato::processBlock(float* const* inputBuffer, int numChannels, int numSamples) {

	for (int s = 0; s < numSamples; ++s) {
		auto sampleL = inputBuffer[0][s];
		auto sampleR = inputBuffer[1][s];

		float vibRate = 0.85f * pow(vibRateParam.next(), 6.0f) * 0.02f;
		float vibDepth = (pow(vibDepthParam.next(), 3)) * 400.0;
		float fmRate = pow(0.1 + fmRateParam.next(), 8) * 0.2f;
		float fmDepth = pow(fmDepthParam.next(), 3);

		ringBuffers[0].write(sampleL);
		ringBuffers[1].write(sampleR);

		float offset = vibDepth + (vibDepth * sin(vibPhase));
		float delayReadL = ringBuffers[0].read(offset);
		float delayReadR = ringBuffers[1].read(offset);

		vibPhase += (vibRate + (fmRate * sin(fmPhase) * fmDepth));
		fmPhase += fmRate;

		if (vibPhase > TWO_PI) { vibPhase -= TWO_PI; }
		if (vibPhase < 0.0) { vibPhase += TWO_PI; }
		if (fmPhase > TWO_PI) { fmPhase -= TWO_PI; }

		auto wet = mix.next();

		float cutoff = cutoffParam.next();

		filterL.setCutoff(cutoff);
		delayReadL = filterL.process(delayReadL);
		filterR.setCutoff(cutoff);
		delayReadR = filterR.process(delayReadR);

		inputBuffer[0][s] = sampleL * (1.0f - wet) + delayReadL * wet;
		inputBuffer[1][s] = sampleR * (1.0f - wet) + delayReadR * wet;
	}
}