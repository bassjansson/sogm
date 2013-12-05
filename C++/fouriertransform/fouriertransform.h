
#include <cmath>

using namespace std;

float * spec[] = {new float[8192], new float[8192]};
float * pol[] = {new float[8192], new float[8192]};

float ** fourierTransform(float * sig, int window) {
	int specwindow = window/2;

	for(int b = 0; b < specwindow; b++) {			// walk through the bins (spectrum)
		float amps[] = {0, 0};						// amplitudes of the bin set to 0
		float alpha = (b + 1) * 2*M_PI / window;	// binnumber * 2pi / window
    
		// walk through the input signal and multiply it with the sin and cos waves
		// and keep adding each product to magnitude to get the magnitude of the bin
		for(int i = 0; i < window; i++) {
			amps[0] += sin(alpha * i) * sig[i];
			amps[1] += cos(alpha * i) * sig[i];
		}
    
		spec[0][b] = amps[0] / specwindow;
		spec[1][b] = amps[1] / specwindow;
	}

	return spec;
}

float ** carToPol(float ** car, int window) {
	float re, im;
	
	for(int i = 0; i < window; i++) {
		re = car[0][i];
		im = car[1][i];
		
		// Calculate Magnitude
		pol[0][i] = sqrt(pow(re, 2) + pow(im, 2));
		
		// Calculate Phase
		if(re == 0) pol[1][i] = fmod(              2.0*M_PI + im/abs(im)*M_PI/2, 2*M_PI);
		else        pol[1][i] = fmod(atan(im/re) + 1.5*M_PI + re/abs(re)*M_PI/2, 2*M_PI);
	}
	
	return pol;
}

