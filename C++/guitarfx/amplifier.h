// amplifier.h

#include "audiofx.h"

class Amplifier : public AudioFX {
	public:
		Amplifier(int buffer_size);

        void processSamples(int frame_size, int channels);
		int  paramSwitch(char param, float value);

    private:
        float gain;
};

