// bitcrusher.cpp

#include "bitcrusher.h"
#include <cmath>

//==================================================================
Bitcrusher::Bitcrusher()
{
	bitdepth = 2;
	rounding = 0;
}

//==================================================================
void Bitcrusher::processSamples(BufferInfo* bufferToChange)
{
	double depth = pow(2.0, (double)bitdepth - 1);

	for(int c = 0; c < bufferToChange->numOfChannels; c++)
	{
		for(int s = 0; s < bufferToChange->bufferSize; s++)
		{
			double value = bufferToChange->buffer[c][s] * depth;

			switch(rounding)
			{
				default: bufferToChange->buffer[c][s] =  ceil(value) / depth; break;
            	case 0 : bufferToChange->buffer[c][s] =  ceil(value) / depth; break;
				case 1 : bufferToChange->buffer[c][s] = round(value) / depth; break;
				case 2 : bufferToChange->buffer[c][s] = floor(value) / depth; break;
			}
		}
	}
}		

int Bitcrusher::paramSwitch(char param, float value)
{
	switch(param)
	{
		default : return 0;
		case 'b': bitdepth = (int)value; return 2;
		case 'r': rounding = (int)value; return 2;
	}
}

