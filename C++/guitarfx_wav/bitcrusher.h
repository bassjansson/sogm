// bitcrusher.h

#include "audiofx.h"

class Bitcrusher : public AudioFX {
	public:
		// From Bitcrusher itself
		Bitcrusher(int blocksize);

		// From AudioFX
        void processSamples();
		int  paramSwitch(char param, float value);

    private:
        int bitdepth;
		int rounding;
};

