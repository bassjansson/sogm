// amplifier.h

#define BUFFER_SIZE 1024

class Amplifier {
	public:
		Amplifier();
		void readSamples();
		void processSamples();
		void writeSamples();
		void process();
		float level;

	private:
		float * sig;
};

