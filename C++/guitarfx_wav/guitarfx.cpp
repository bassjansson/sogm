// guitarfx.cpp

#include <iostream>
#include "effects/audiofx.h"
#include "effects/amplifier.h"
#include "effects/tremelo.h"


void manual() {
	clog <<
"No valid input, usage:\n\n\
    guitarfx [effect] [inputfile] [outputfile] -[param] [value]\n\n\n\
Effects with their parameters:\n\n\
    a [amplifier]\n\
        -g [gain]       Set gain of the amplifier (0 to 1)\n\n\
    t [tremelo]\n\
        -d [depth]      Set depth of the tremelo (0 to 1)\n\
        -f [frequency]  Set frequency of the oscillator (Hertz)\n\
        -p [phase]      Set phase of the oscillator (0 to 1)\n\n";
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

