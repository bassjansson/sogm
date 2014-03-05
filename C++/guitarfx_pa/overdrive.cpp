// overdrive.cpp

#include "overdrive.h"
#include <cmath>

//==================================================================
Overdrive::Overdrive()
{
	drive = 0.25f;
}

//==================================================================
void Overdrive::processSamples(BufferInfo* bufferToChange)
{
	for(int c = 0; c < bufferToChange->numOfChannels; c++)
	{
		for(int s = 0; s < bufferToChange->bufferSize; s++)
		{
			if(drive < 0.0001) drive = 0.0001;
			bufferToChange->buffer[c][s] = powf(bufferToChange->buffer[c][s], drive);
		}
	}
}		

int Overdrive::paramSwitch(char param, float value)
{
	switch(param)
	{
		default : return 0;
		case 'd': drive = value; return 2;
	}
}

