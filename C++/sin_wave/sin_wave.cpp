
#include <iostream>
#include <cmath>

#define SAMPLERATE 48000

using namespace std;

int main() {
	int freq = 480;
	int window = SAMPLERATE / freq; // 1 periode

	for(int i = 0; i < window; i++) {
		cout << sin((double)i / window * 2*M_PI) << endl;
	}
}

