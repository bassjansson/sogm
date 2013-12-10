
#include <cmath>

using namespace std;

float * buf[] = {new float[8192], new float[8192]};
float * sig = new float[16384];


float modulo(float a, float b) {
	return ((a / b) - int(a / b)) * b;
}


float ** carToPol(float ** car, int window) {	
	for(int i = 0; i < window; i++) {
		float re = car[0][i];
		float im = car[1][i];
		
		// Calculate Magnitude
		buf[0][i] = sqrt(pow(re, 2) + pow(im, 2));
		
		// Calculate Phase
		if(re == 0) buf[1][i] = modulo(              2.0*M_PI + im/abs(im)*M_PI/2, 2*M_PI);
		else        buf[1][i] = modulo(atan(im/re) + 1.5*M_PI + re/abs(re)*M_PI/2, 2*M_PI);
	}
	
	return buf;
}


float ** fourierTransform(float * sig, int window) {	
	int specwindow = window/2;

	for(int b = 0; b < specwindow; b++) {				// walk through the bins (spectrum)
		float amps[] = {0, 0};							// amplitudes of the bin set to 0
		float alpha = b * 2*M_PI / window;				// binnumber * 2pi / window
    
		// walk through the input signal and multiply it with the sin and cos waves
		// and keep adding each product to magnitude to get the magnitude of the bin
		for(int i = 0; i < window; i++) {
			amps[0] += sin(alpha * i) * sig[i];
			amps[1] += cos(alpha * i) * sig[i];
		}
    
		buf[0][b] = amps[0] / specwindow;
		buf[1][b] = amps[1] / specwindow;
	}

	return carToPol(buf, specwindow);
}


float * inverseFourierTransform(float ** pol, int window) {	
	int specwindow = window/2;

	for(int b = 0; b < specwindow; b++) {				// walk through the bins (spectrum)
		float alpha = b * 2*M_PI / window;				// binnumber * 2pi / window
    
		for(int i = 0; i < window; i++) {				// walk through the output signal
			if(b == 0) sig[i] = 0;
			sig[i] += sin(alpha * i + pol[1][b]) * pol[0][b];
		}
	}

	return sig;
}

