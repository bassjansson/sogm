// tremelo.cpp

#include <cmath>
#include "tremelo.h"

Tremelo::Tremelo(int blocksize) : AudioFX(blocksize) {
	depth = 1;
	freq  = 8;
	phase = 0;
}

void Tremelo::processSamples() {
    for(int c = 0; c < channels; c++) {
        for(int i = 0; i < blocksize; i++) {
            buffer[c][i + writing] = buffer[c][i + processing] * (sin((double)i / SAMPLERATE * freq * 2*M_PI + phase) * depth/2 + 1 - depth/2);
        }
    }
    phase += (double)blocksize / SAMPLERATE * freq * 2*M_PI;
}

int Tremelo::paramSwitch(char param, float value) {
	switch(param) {
		default : return 0;
		case 'd': depth = value; return 2;
		case 'f': freq  = value; return 2;
		case 'p': phase = value * 2*M_PI; return 2;
	}
}

