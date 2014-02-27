// foldback.cpp

#include "foldback.h"
#include <cmath>

//==================================================================
Foldback::Foldback()
{
	drive = 4.f;
}

//==================================================================
void Foldback::processSamples(BufferInfo* bufferToChange)
{
	for(int c = 0; c < bufferToChange->numOfChannels; c++)
	{
		for(int s = 0; s < bufferToChange->bufferSize; s++)
		{
			float sample = bufferToChange->buffer[c][s];

			bufferToChange->buffer[c][s] = fmod(fabsf(sample) * drive, 1.f) * sample/fabsf(sample);	
		}
	}
}		

int Foldback::paramSwitch(char param, float value)
{
	switch(param)
	{
		default : return 0;
		case 'd': drive = value; return 2;
	}
}

