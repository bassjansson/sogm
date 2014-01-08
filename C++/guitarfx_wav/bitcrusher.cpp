// bitcrusher.cpp

#include "bitcrusher.h"
#include <cmath>

// From Bitcrusher itself
Bitcrusher::Bitcrusher(int blocksize) : AudioFX(blocksize) {
	bitdepth = 4;
	rounding = 0;
}

// From AudioFX
void Bitcrusher::processSamples() {
	double depth = pow(2, bitdepth - 1);

    for(int c = 0; c < channels; c++) {
        for(int i = 0; i < blocksize; i++) {
			double sample = buffer[c][i + processing] * depth;

			switch(rounding) {
				default: buffer[c][i + writing] =  ceil(sample) / depth; break;
            	case 0 : buffer[c][i + writing] =  ceil(sample) / depth; break;
				case 1 : buffer[c][i + writing] = round(sample) / depth; break;
				case 2 : buffer[c][i + writing] = floor(sample) / depth; break;
			}
        }
    }
}

int Bitcrusher::paramSwitch(char param, float value) {
	switch(param) {
		default : return 0;
		case 'b': bitdepth = (int)value; return 2;
		case 'r': rounding = (int)value; return 2;
	}
}

