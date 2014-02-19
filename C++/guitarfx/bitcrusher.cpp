// bitcrusher.cpp

#include "bitcrusher.h"
#include <cmath>

Bitcrusher::Bitcrusher(int buffer_size) : AudioFX(buffer_size)
{
	bitdepth = 4;
	rounding = 0;
}


void Bitcrusher::processSamples(int frame_size, int channels) {
	double depth = pow(2, bitdepth - 1);

    for(int s = 0; s < frame_size; s++)
	{
		for(int c = 0; c < channels; c++)
		{
			int place = getSamplePlace(s, c);
			double value = buffer[place] * depth;

			switch(rounding)
			{
				default: buffer[place] =  ceil(value) / depth; break;
            	case 0 : buffer[place] =  ceil(value) / depth; break;
				case 1 : buffer[place] = round(value) / depth; break;
				case 2 : buffer[place] = floor(value) / depth; break;
			}
        }
    }
}

int Bitcrusher::paramSwitch(char param, float value) {
	switch(param)
	{
		default : return 0;
		case 'b': bitdepth = (int)value; return 2;
		case 'r': rounding = (int)value; return 2;
	}
}

