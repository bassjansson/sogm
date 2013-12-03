// My Fourier Transform Program in C++

#include <iostream>
#include <math.h>

using namespace std;

// Defining global variables
int sr;
int window;
char waveform[3];
float freq;
float phase;

const int windowmax = 1024;
float sig[windowmax];


void getInput() {
	cout << "Samplerate: ";
	cin >> sr;
	cout << "Windowsize: ";
	cin >> window;
	cout << "Waveform: ";
	cin >> waveform;
	cout << "Frequency: ";
	cin >> freq;
	cout << "Phase: ";
	cin >> phase;
	cout << endl;
}

float genSin(int window, float freq, float phase) [windowmax] {
	float sig[windowmax];
	for(int i = 0; i < window; i++) {
		sig[i] = sin(2*M_PI * (freq / sr * i + phase));
	}
	return sig;
}

float genCos(int window, float freq, float phase) [windowmax] {
	float sig[windowmax];
	for(int i = 0; i < window; i++) {
		sig[i] = cos(2*M_PI * (freq / sr * i + phase));
	}
	return sig;
}

float genTri(int window, float freq, float phase) [windowmax] {
	float sig[windowmax];
	for(int i = 0; i < window; i++) {
		sig[i] = abs(((freq / sr * i + phase + 0.25) % 1.) * 2 - 1) * 2 - 1;
	}
	return sig;
}

float genRec(int window, float freq, float phase) [windowmax] {
	float sig[windowmax];
	for(int i = 0; i < window; i++) {
		sig[i] = int(((freq / sr * i + phase) % 1.) * 2) * 2 - 1;
	}
	return sig;
}

float genSaw(int window, float freq, float phase) [windowmax] {
	float sig[windowmax];
	for(int i = 0; i < window; i++) {
		sig[i] = ((freq / sr * i + phase) % 1.) * 2 - 1;
	}
	return sig;
}

float genSignal(char waveform[3], int window, float freq, float phase) [windowmax] {
	switch(waveform[1]) {
		case 'i': return genSin(window, freq, phase); break;
		case 'o': return genCos(window, freq, phase); break;
		case 'r': return genTri(window, freq, phase); break;
		case 'e': return genRec(window, freq, phase); break;
		case 'a': return genSaw(window, freq, phase); break;
		default:	return genSin(window, freq, phase); break;
	}
}

// Main
int main() {
	getInput();
	sig = genSignal(waveform, window, freq, phase);
	cout << sig << endl;
	
	return 0;
}

