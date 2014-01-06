// amplifier.h

#include "audiofx.h"

class Amplifier: public AudioFX {
	public:
		// From Amplifier itself
		Amplifier();
		float gain;
		
		// From AudioFX
		int paramSwitch(char param, float value);
		void processSamples();
};

