// guitarfx.cpp

#include <iostream>
#include <cstdlib>

#include "audio_io.h"
#include "audiofx.h"

#include "amplifier.h"
#include "tremelo.h"
#include "bitcrusher.h"
#include "chorus.h"
#include "overdrive.h"
#include "dynamiccompressor.h"


int manual()
{
	clog <<
"No valid input, usage and example:\n\n\
\tguitarfx [effect] -[parameter] [value]\n\n\
\tguitarfx tremelo -d 0.8 -f 10 chorus -f 3 amp -g 0.5\n\n\n\
Effects with their parameters:\n\n\
\ta(mplifier)\n\
\t\t-g(ain)       [0 to 1]    Set gain of the amplifier\n\n\
\tt(remelo)\n\
\t\t-d(epth)      [0 to 1]    Set depth of the tremelo\n\
\t\t-f(requency)  [Hertz]     Set frequency of the oscillator\n\
\t\t-p(hase)      [0 to 1]    Set phase of the oscillator\n\n\
\tb(itcrusher)\n\
\t\t-b(itdepth)   [1 to 15]   Set bitdepth of the bitcrusher\n\
\t\t-r(ounding)   [0, 1, 2]   Set rounding of the bitcrusher\n\
\t\t                          0 = ceiling, 1 = round, 2 = floor\n\n\
\tc(horus)\n\
\t\t-d(epth)      [Seconds]   Set depth of the chorus\n\
\t\t-f(requency)  [Hertz]     Set frequency of the oscillator\n\
\t\t-p(hase)      [0 to 1]    Set phase of the oscillator\n\n\
\to(verdrive)\n\
\t\t-d(rive)      [0 to ∞]    Set drive of the overdrive\n\n\
\td(ynamic compressor)\n\
\t\t-i(nterval)   [Seconds]   Set interval of the RMS\n\n\
\t\t-r(atio)      [0 to ∞]    Set ratio of the Compressor\n\n";

	return 1;
}


#define SAMPLERATE		   48000
#define NUM_OF_CHANNELS    1
#define MAX_NUM_OF_EFFECTS 10


int main(int argc, char * argv[])
{
	// If less then 1 argument is given
    // show manual and quit
	if(argc < 2) return manual();


	// Create an audio effect array,
	// set current effect to zero
    // and set current argument to one
	AudioFX** effect = new AudioFX*[MAX_NUM_OF_EFFECTS];
	int afx = 0;
    int arg = 1;    


	// Process the given arguments
	while(arg < argc)
	{
		if(argv[arg][0] == '-')
		{
			if(effect[afx - 1] != nullptr)
			{
				int result = effect[afx - 1]->paramSwitch(argv[arg][1], atof(argv[arg+1]));

				if(result > 0)
				{
        			arg += result;
            	}
				else return manual();
			}
			else return manual();
		}
		else {
			if(afx < MAX_NUM_OF_EFFECTS)
			{
	            switch(argv[arg][0])
				{
					default : return manual();
	
					case 'a': effect[afx] = new Amplifier();
							  arg++; afx++; break;
	
					case 't': effect[afx] = new Tremelo();               
							  arg++; afx++; break;

					case 'b': effect[afx] = new Bitcrusher();
							  arg++; afx++; break;

					case 'c': effect[afx] = new Chorus();
							  arg++; afx++; break;

					case 'f': effect[afx] = new Overdrive();
							  arg++; afx++; break;

					case 'd': effect[afx] = new DynamicCompressor();
							  arg++; afx++; break;
				}
			}
			else return manual();
        }
	}


	// Get buffersize
	int BUFFER_SIZE;
	cout << "\nGive buffersize: ";
	cin >> BUFFER_SIZE;


	// Initialise audio I/O
	Audio_IO audioIO;

	audioIO.set_mode(AUDIO_IO_READWRITE);
	audioIO.set_samplerate(SAMPLERATE);
	audioIO.set_framesperbuffer(BUFFER_SIZE);
	audioIO.set_nrofchannels(NUM_OF_CHANNELS);

	audioIO.initialise();
	audioIO.list_devices();
	int device;

	cout << "\nGive input device number: ";
	cin >> device;
	audioIO.set_input_device(device);

	cout << "Give output device number: ";
	cin >> device;
	audioIO.set_output_device(device);

	audioIO.start_server();


	// Initialise the effects
	for(int i = 0; i < afx; i++)
		effect[i]->initialise(SAMPLERATE, BUFFER_SIZE, NUM_OF_CHANNELS);


	// Read, process and write audio
	while(true)
	{
		audioIO.read(effect[0]->getBuffer());

		effect[0]->process();
		for(int i = 1; i < afx; i++)
			effect[i]->process(effect[i - 1]->getBuffer());

		audioIO.write(effect[afx - 1]->getBuffer());
	}


	// Finalise audio I/O
	// and exit program
	audioIO.finalise();
	return 0;
}

