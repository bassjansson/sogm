// audiofx.cpp

#include <iostream>
#include "audiofx.h"

using namespace std;

// Members which can't be modified
AudioFX::AudioFX() {
	buffer = new float[BUFFER_SIZE];
}

void AudioFX::readSamples() {
	for(int i = 0; i < BUFFER_SIZE; i++) {
		cin >> buffer[i];
	}
}

void AudioFX::writeSamples() {
	for(int i = 0; i < BUFFER_SIZE; i++) {
		cout << buffer[i] << endl;
	}
}

void AudioFX::process() {
	readSamples();
	processSamples();
	writeSamples();
}

// Members which can be modified by a derived class
int AudioFX::paramSwitch(char param, float value) {
	return 0;
}

void AudioFX::processSamples() {

}

