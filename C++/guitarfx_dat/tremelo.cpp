// tremelo.cpp

#include <cmath>
#include "tremelo.h"

Tremelo::Tremelo() {
	depth = 1;
	freq = 8;
	phase = 0;
}

int Tremelo::paramSwitch(char param, float value) {
	switch(param) {
		default : return 0;
		case 'd': depth = value; return 2;
		case 'f': freq  = value; return 2;
		case 'p': phase = value * 2*M_PI; return 2;
	}
}

void Tremelo::processSamples() {
	for(int i = 0; i < BUFFERSIZE; i++) {
		buffer[i] *= sin(phase) * depth/2 + 1 - depth/2;
		phase += 2*M_PI * freq / SAMPLERATE;
	}
}

