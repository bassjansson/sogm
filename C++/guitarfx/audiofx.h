// audiofx.h

#define BUFFERSIZE 1024
#define SAMPLERATE 48000

class AudioFX {
	public:		
		// Members which can't be modified
		AudioFX();
		void readSamples();
		void writeSamples();
		void process();

		// Members which can be modified by a derived class
		virtual int paramSwitch(char param, float value);
		virtual void processSamples();

	protected:
		float * buffer;
};

