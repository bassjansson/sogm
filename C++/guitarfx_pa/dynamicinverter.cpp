// dynamicinverter.cpp

#include "dynamicinverter.h"
#include <cmath>

//==================================================================
DynamicInverter::DynamicInverter()
{
	int sampleRate = 48000;
	int numOfChannels = 2;

	historySize  = sampleRate;
	historyPlace = 0;

	history = new float*[numOfChannels];
	for(int c = 0; c < numOfChannels; c++)
		history[c] = new float[historySize];

	interval = 0.4;
	newRMS = new float[numOfChannels];
	oldRMS = new float[numOfChannels];
}

DynamicInverter::~DynamicInverter()
{
	delete history;
	delete newRMS;
	delete oldRMS;
}

//==================================================================
void DynamicInverter::processSamples(BufferInfo* bufferToChange)
{
	int intervalInSampels = int(interval * bufferToChange->sampleRate);

	for(int c = 0; c < bufferToChange->numOfChannels; c++)
	{
		// Updating newRMS
		newRMS[c] = 0.0f;
		for(int i = 0; i < intervalInSampels; i++)
		{
			int sample = (historySize + historyPlace - i) % historySize;
			newRMS[c] += history[c][sample] * history[c][sample];
		}
		newRMS[c] = sqrtf(newRMS[c] / intervalInSampels);

		// Writing buffer
		for(int s = 0; s < bufferToChange->bufferSize; s++)
		{
			// Writing to history
			int sample = (s + historyPlace) % historySize;
			history[c][sample] = bufferToChange->buffer[c][s];

			// Writing sample
			float rms = oldRMS[c] + (newRMS[c] - oldRMS[c]) * s / bufferToChange->bufferSize;
			bufferToChange->buffer[c][s] *= (1.f / (sqrtf(rms) + 0.000001) - 1.f);
		}

		// Updating oldRMS
		oldRMS[c] = newRMS[c];
	}

	// Updating historyplace
	historyPlace = (bufferToChange->bufferSize + historyPlace) % historySize;
}

int DynamicInverter::paramSwitch(char param, float value)
{
	switch(param)
	{
		default : return 0;
		case 'i': interval = value; return 2;
	}
}

