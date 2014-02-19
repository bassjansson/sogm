// audiofx.h

#ifndef _AUDIOFX_H_
#define _AUDIOFX_H_

#include "audio_io.h"

using namespace std;

class AudioFX : public Audio_IO
{
	public:
		AudioFX(int buffer_size);
		~AudioFX();

		void setAudioSettings(int samplerate, int frame_size, int channels);
		void startAudio();
		void stopAudio();
		void process();
		int  getSamplePlace(int sample, int channel);

		virtual void processSamples(int frame_size, int channels);
        virtual int  paramSwitch(char param, float value);

	protected:
		long   buffer_place;
		int    buffer_size;
		float* buffer;
};

#endif // _AUDIOFX_H_

