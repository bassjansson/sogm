// audiofx.h

#ifndef _AUDIOFX_H_
#define _AUDIOFX_H_

#define SAMPLERATE 48000
#define HEADERSIZE 44
#define BYTEDEPTH 2
#define ABSDEPTH 32767
#define MAXCHANNELS 5

#include <fstream>
#include <cmath>

using namespace std;

class AudioFX {
	public:		
		// Members which can't be modified
		AudioFX(int blocksize);
        ~AudioFX();

        bool openFile(char * filename);
        bool createFile(char * filename);

        void circulate(int block);
		void readSamples(ifstream * file, int block);
		void writeSamples(ofstream * file, int block);

		// Members which can be modified by a derived class
		virtual void processSamples();
        virtual void process();
        virtual int  paramSwitch(char param, float value);

	protected:
        int blocksize;
        int buffersize;

		double ** buffer;
        char * header;
        
        ifstream inputfile;
        ofstream outputfile;

        int filesize;
        int channels;

        int history;
        int processing;
        int reading;
        int writing;
};

#endif

