// tremelo.h

#include "amplifier.h"

class Tremelo: public AudioFX {
	public:
		// From Tremelo itself
		Tremelo();
		float depth;
		float freq;
		float phase;
		
		// From AudioFX
		int paramSwitch(char param, float value);
		void processSamples();
};

