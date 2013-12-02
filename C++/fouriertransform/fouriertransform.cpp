// my fast fourier program in C++

#include <iostream>
#include <math.h>

using namespace std;

int main() {
	float samplerate;
	float freq;
	float phase;
	float samplelength;
	
	cout << "Samplerate: ";
	cin >> samplerate;
	cout << "Frequency: ";
	cin >> freq;
	cout << "Phase: ";
	cin >> phase;
	cout << "Length in Samples: ";
	cin >> samplelength;
	cout << endl;

	for(int i = 0; i < samplelength; i++) {
		float amp = sin(2*M_PI * (freq / samplerate) * i + 2*M_PI * phase);
		float iamp = int(amp * 10000) / 10000.;
		clog << iamp << endl;
	}
	
	return 0;
}
