
#include <iostream>
#include "signalgenerator.h"
#include "fouriertransform.h"

using namespace std;

// Wave Switch
float (* waveSwitch(char wave[]))(int, float, float) {
	switch(wave[2]) {
		case 'a': return &phasor; break;
		case 'n': return &sinwave; break;
		case 's': return &coswave; break;
		case 'i': switch(wave[0]) {
					case 't': return &triangle; break;
					case 'n': return &noise; break;
					default : return &noise; break;
				  } break;
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

	// Get input from the command line
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

	// Generate the signal and the Slow Fourier Transform of the signal
	float *  sig = genSignal(waveSwitch(waveform), window, freq, phase);
	float ** sft = fourierTransform(sig, window);
	float * tsig = inverseFourierTransform(sft, window);

	// Print sig and sft on the command line
	for(int i = 0; i < window; i++) {
			 clog << i						<< "	";
			 clog << sig[i]				+ 2 << "	";
			 clog << tsig[i]				<< "	";
		if(i < window/2) {
			 clog << i*2					<< "	";
			 clog << sft[0][i]			- 2 << "	";
			 clog << sft[1][i]/(2*M_PI) - 3	<< endl;
		}
		else clog << endl;
	}

	return 0;
}

//          fun              -- fun
//          fun(    )        -- is a function
//          fun(char)        -- 	taking a char parameter
//        * fun(char)        -- 	returning a pointer
//       (* fun(char))(   )  -- 	to a function
//       (* fun(char))(int)  -- 		taking a int parameter
// float (* fun(char))(int)  -- 		returning float

