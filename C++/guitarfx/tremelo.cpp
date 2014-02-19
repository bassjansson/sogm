// tremelo.cpp

#include <cmath>
#include "tremelo.h"

Tremelo::Tremelo(int buffer_size) : AudioFX(buffer_size)
{
	depth = 1;
	freq  = 8;
	phase = 0;
}


void Tremelo::processSamples(int frame_size, int channels)
{
    for(int s = 0; s < frame_size; s++)
	{
		for(int c = 0; c < channels; c++)
		{
			int place = getSamplePlace(s, c);
            buffer[place] *= (sin((double)s / samplerate * freq * 2*M_PI + phase) * depth/2 + 1 - depth/2);
        }
    }

    phase += (double)frame_size / samplerate * freq * 2*M_PI;
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

