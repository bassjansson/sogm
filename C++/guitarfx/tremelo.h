// tremelo.h

#include "audiofx.h"

class Tremelo : public AudioFX {
	public:
		Tremelo(int buffer_size);
		
        void processSamples(int frame_size, int channels);
		int  paramSwitch(char param, float value);

    private:
        float depth;
		float freq;
		float phase;
};

