
#include <iostream>
#include "signalgenerator.h"
#include "fouriertransform.h"

using namespace std;

//          fun              -- fun
//          fun(    )        -- is a function
//          fun(char)        -- 	taking a char parameter
//        * fun(char)        -- 	returning a pointer
//       (* fun(char))(   )  -- 	to a function
//       (* fun(char))(int)  -- 		taking a int parameter
// float (* fun(char))(int)  -- 		returning float

// Wave Switch
float (* waveSwitch(char wave[]))(int, float, float) {
	switch(wave[2]) {
		case 'a': return &phasor; break;
		case 'n': return &sinwave; break;
		case 's': return &coswave; break;
		case 'i': return &triangle; break;
		case 'c': return &rectangle; break;
		case 'w': return &sawwave; break;
		default : return &sinwave; break;
	}
}

// Main
int main() {

	char waveform[3];
	int window;
	float freq;
	float phase;

	cout << "Samplerate = 48000 Hz\n";
	cout << "Waveform: ";
	cin >> waveform;
	cout << "Windowsize: ";
	cin >> window;
	cout << "Frequency: ";
	cin >> freq;
	cout << "Phase: ";
	cin >> phase;
	cout << endl;

	float * sig = genSignal(waveSwitch(waveform), window, freq, phase);
	for(int i = 0; i < window; i++) clog << i << "	" << sig[i] << endl;
		
	return 0;
}

