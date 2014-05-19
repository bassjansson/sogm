// amplifier.h

#include "audiofx.h"

class Amplifier : public AudioFX {
	public:
		// From Amplifier itself
		Amplifier(int blocksize);

		// From AudioFX
        void processSamples();
		int  paramSwitch(char param, float value);

    private:
        float gain;
};

