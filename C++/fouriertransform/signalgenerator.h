
#include <cmath>

using namespace std;

// Samplerate and Signal Buffer
unsigned int sr = 48000;
float signalbuffer[1024];

// Wave Calculators
float phasor(int sample, float freq, float phase) {
	return fmod(freq / sr * sample + phase, 1.);
}

float sinwave(int sample, float freq, float phase) {
	return sin(phasor(sample, freq, phase) * 2*M_PI);
}

float coswave(int sample, float freq, float phase) {
	return cos(phasor(sample, freq, phase) * 2*M_PI);
}

float triangle(int sample, float freq, float phase) {
	return abs(phasor(sample, freq, phase+0.75) * 2 - 1) * 2 - 1;
}

float rectangle(int sample, float freq, float phase) {
	return int(phasor(sample, freq, phase) * 2) * 2 - 1;
}

float sawwave(int sample, float freq, float phase) {
	return phasor(sample, freq, phase) * 2 - 1;
}

// Signal Generator
float * genSignal(float (*waveCalc)(int, float, float), int window, float freq, float phase) {
	for(int i = 0; i < window; i++) {
		signalbuffer[i] = (*waveCalc)(i, freq, phase);
	}
	float * sigpointer = signalbuffer;
	return sigpointer;
}

