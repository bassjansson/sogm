// amplifier.cpp

#include "amplifier.h"

//==================================================================
Amplifier::Amplifier()
{
	gain = 0.5f;
}

//==================================================================
void Amplifier::processSamples(BufferInfo* bufferToChange)
{
	for(int c = 0; c < bufferToChange->numOfChannels; c++)
	{
		for(int s = 0; s < bufferToChange->bufferSize; s++)
		{
			bufferToChange->buffer[c][s] *= gain;
		}
	}
}

int Amplifier::paramSwitch(char param, float value)
{
	switch(param)
	{
		default : return 0;
		case 'g': gain = value; return 2;
	}
}

