// amplifier.cpp

#include "amplifier.h"

// From Amplifier itself
Amplifier::Amplifier(int blocksize) : AudioFX(blocksize) {
	gain = 1;
}

// From AudioFX
void Amplifier::processSamples() {
    for(int c = 0; c < channels; c++) {
        for(int i = 0; i < blocksize; i++) {
            buffer[c][i + writing] = buffer[c][i + processing] * gain;
        }
    }
}

int Amplifier::paramSwitch(char param, float value) {
	switch(param) {
		default : return 0;
		case 'g': gain = value; return 2;
	}
}

