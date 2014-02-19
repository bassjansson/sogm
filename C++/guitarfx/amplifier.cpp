// amplifier.cpp

#include "amplifier.h"

Amplifier::Amplifier(int buffer_size) : AudioFX(buffer_size)
{
	gain = 1;
}


void Amplifier::processSamples(int frame_size, int channels)
{
   	for(int s = 0; s < frame_size; s++)
	{
		for(int c = 0; c < channels; c++)
		{
			int place = getSamplePlace(s, c);
			buffer[place] *= gain;
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

