// tremelo.cpp

#include "tremelo.h"
#include <cmath>

//==================================================================
Tremelo::Tremelo()
{
	depth = 1.0f;
	freq  = 8.0f;
	phase = 0.0f;
}

//==================================================================
void Tremelo::processSamples(BufferInfo* bufferToChange)
{
	for(int c = 0; c < bufferToChange->numOfChannels; c++)
	{
		for(int s = 0; s < bufferToChange->bufferSize; s++)
		{
			bufferToChange->buffer[c][s] *=
				( sin((double)s / bufferToChange->sampleRate * freq * 2*M_PI + phase)
				  * depth/2 + 1 - depth/2 );
		}
	}

	phase += (double)bufferToChange->bufferSize / bufferToChange->sampleRate * freq * 2*M_PI;
}

int Tremelo::paramSwitch(char param, float value)
{
	switch(param)
	{
		default : return 0;
		case 'd': depth = value; return 2;
		case 'f': freq  = value; return 2;
		case 'p': phase = value * 2*M_PI; return 2;
	}
}

