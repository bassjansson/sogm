// tremelo.h

#include "audiofx.h"

class Tremelo : public AudioFX {
	public:
		// From Tremelo itself
		Tremelo(int blocksize);
		
		// From AudioFX
        void processSamples();
		int  paramSwitch(char param, float value);

    private:
        float depth;
		float freq;
		float phase;
};

