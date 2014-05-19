// guitarfx.cpp

#include <iostream>
#include "audiofx.h"
#include "amplifier.h"
#include "tremelo.h"
#include "bitcrusher.h"


void manual() {
	clog <<
"\n(note: momentary only compatible with 16 bit 48 kHz wav files (mono and stereo))\n\n\
No valid input, usage and example:\n\n\
\tguitarfx [effect] [inputfile] [outputfile] -[parameter] [value]\n\n\
\tguitarfx tremelo el_gtr.wav el_gtr_trem.wav -d 0.8 -f 10\n\n\n\
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


int main(int argc, char * argv[]) {

	// If less then three arguments are given
    // show manual and quit
	if(argc < 4) {
		manual(); return 0;
	}
    

	// Create an effect
    // and set current argument to one
	AudioFX * effect;
    int arg = 1;


    // Switch effect by first argument
    switch(argv[arg][0]) {
        default : manual(); return 0;
		case 'a': effect = new Amplifier(1024);
                  arg++; break;
        case 't': effect = new Tremelo(1024);               
                  arg++; break;
		case 'b': effect = new Bitcrusher(1024);
				  arg++; break;
    }


    // Open inputfile and create outputfile
    // show manual and quit if open or create failed
    if(effect->openFile(argv[arg]) && effect->createFile(argv[arg+1])) {
        arg += 2;
    }
    else {
        manual(); return 0;
    }


	// Process remaining arguments
    // these are the parameters of the effect
	while(arg < argc) {
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


	// Process the effect
	effect->process();


	// Program finished
	return 0;
}

