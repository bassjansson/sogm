// bitcrusher.h

#include "audiofx.h"

class Bitcrusher : public AudioFX {
	public:
		Bitcrusher(int buffer_size);

        void processSamples(int frame_size, int channels);
		int  paramSwitch(char param, float value);

    private:
        int bitdepth;
		int rounding;
};

