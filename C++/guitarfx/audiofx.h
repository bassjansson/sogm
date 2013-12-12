// audiofx.h

#define BUFFER_SIZE 1024

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

