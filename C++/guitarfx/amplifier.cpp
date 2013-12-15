// amplifier.cpp

#include "amplifier.h"

Amplifier::Amplifier() {
	gain = 1;
}

int Amplifier::paramSwitch(char param, float value) {
	switch(param) {
		default : return 0;
		case 'g': gain = value; return 2;
	}
}

void Amplifier::processSamples() {
	for(int i = 0; i < BUFFERSIZE; i++) {
		buffer[i] *= gain;
	}
}

