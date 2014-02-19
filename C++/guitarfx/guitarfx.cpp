// guitarfx.cpp

#include <iostream>
#include "audiofx.h"

#include "amplifier.h"
#include "tremelo.h"
#include "bitcrusher.h"


void manual()
{
	clog <<
"No valid input, usage and example:\n\n\
\tguitarfx [effect] -[parameter] [value]\n\n\
\tguitarfx tremelo -d 0.8 -f 10\n\n\n\
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
\t\t                          0 = ceiling, 1 = round, 2 = floor\n\n";
}


#define SAMPLERATE   48000
#define FRAME_SIZE   512
#define HISTORY_SIZE 3
#define CHANNELS     2


int main(int argc, char * argv[])
{

	// If less then 1 argument is given
    // show manual and quit
	if(argc < 2)
	{
		manual(); return 0;
	}
    

	// Create an effect,
	// Create a buffer with buffer_size
    // and set current argument to one
	AudioFX * effect;
    int arg = 1;


    // Switch effect by first argument
	int buffer_size = FRAME_SIZE * CHANNELS * HISTORY_SIZE;
    switch(argv[arg][0])
	{
        default : manual(); return 0;
		case 'a': effect = new Amplifier(buffer_size);
                  arg++; break;
        case 't': effect = new Tremelo(buffer_size);               
                  arg++; break;
		case 'b': effect = new Bitcrusher(buffer_size);
				  arg++; break;
    }


	// Process remaining arguments
    // these are the parameters of the effect
	while(arg < argc)
	{
		if(argv[arg][0] == '-') {
			int result = effect->paramSwitch(argv[arg][1], atof(argv[arg+1]));
			if(result > 0) {
                arg += result;
            }
			else {
                manual(); return 0;
            }
		}
		else {
            manual(); return 0;
        }
	}


	// Set audio settings
	effect->setAudioSettings(SAMPLERATE, FRAME_SIZE, CHANNELS);


	// Start, read, process, write and stop audio
	effect->startAudio();
	while(true) effect->process();
	effect->stopAudio();


	// Program finished
	return 0;
}

