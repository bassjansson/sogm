// chorus.cpp

#include "chorus.h"
#include <cmath>

//==================================================================
Chorus::Chorus()
{
	int sampleRate = 48000;
	int numOfChannels = 2;

	historySize  = sampleRate;
	historyPlace = 0;

	history = new float*[numOfChannels];
	for(int c = 0; c < numOfChannels; c++)
		history[c] = new float[historySize];

	depth = 0.01f;
	freq  = 2.0f;
	phase = 0.0f;
}

Chorus::~Chorus()
{
	delete history;
}

//==================================================================
void Chorus::processSamples(BufferInfo* bufferToChange)
{
	for(int c = 0; c < bufferToChange->numOfChannels; c++)
	{
		// Writing buffer
		for(int s = 0; s < bufferToChange->bufferSize; s++)
		{
			// Writing to history
			int sample = (s + historyPlace) % historySize;
			history[c][sample] = bufferToChange->buffer[c][s];

			// Calculating delay
			int delay  = ( sin((double)s / bufferToChange->sampleRate * freq * 2*M_PI + phase)
						   / 2.0 + 0.5 ) * depth * bufferToChange->sampleRate;

			// Writing sample
			sample = (s + historyPlace + historySize - delay) % historySize;
			bufferToChange->buffer[c][s] += history[c][sample];
		}
	}

	// Updating history and phase
	historyPlace = (bufferToChange->bufferSize + historyPlace) % historySize;
	phase += (double)bufferToChange->bufferSize / bufferToChange->sampleRate * freq * 2*M_PI;
}

int Chorus::paramSwitch(char param, float value)
{
	switch(param)
	{
		default : return 0;
		case 'd': depth = value; return 2;
		case 'f': freq  = value; return 2;
		case 'p': phase = value * 2*M_PI; return 2;
	}
}

