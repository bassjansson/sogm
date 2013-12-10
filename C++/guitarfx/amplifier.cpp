// amplifier.cpp

#include <iostream>
#include "amplifier.h"

using namespace std;

Amplifier::Amplifier() {
	sig = new float[BUFFER_SIZE];
	level = 1;
}

void Amplifier::readSamples() {
	for(int i = 0; i < BUFFER_SIZE; i++) {
		cin >> sig[i];
	}
}

void Amplifier::processSamples() {
	for(int i = 0; i < BUFFER_SIZE; i++) {
		sig[i] *= level;
	}
}

void Amplifier::writeSamples() {
	for(int i = 0; i < BUFFER_SIZE; i++) {
		cout << sig[i] << endl;
	}
}

void Amplifier::process() {
	readSamples();
	processSamples();
	writeSamples();
}

