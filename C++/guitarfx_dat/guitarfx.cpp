// guitarfx.cpp

#include <iostream>
#include "tremelo.h"

using namespace std;

void manual() {
	clog << "No valid input, usage:\n\
	guitarfx [effect] -[param] [value] < [inputfile] > [outputfile]\n";
}

int main(int argc, char * argv[]) {

	// Create an Audio Effect
	AudioFX * effect;

	// If no arguments are given, show manual
	if(argc < 2) {
		manual(); return 0;
	}

	// Select effect by first argument
	switch(argv[1][0]) {
		default : manual(); return 0;
		case 'a': effect = new Amplifier; break;
		case 't': effect = new Tremelo; break;
	}

	// Process remaining arguments
	int arg = 2;
	while(arg < argc) {
		if(argv[arg][0] == '-') {
			int result = effect->paramSwitch(argv[arg][1], atof(argv[arg+1]));
			if(result < 1) {
				manual(); return 0;
			}
			else arg += result;
		}
		else {
			if(argv[arg][0] == '<' || argv[arg][0] == '>') arg += 2;
			else {
				manual(); return 0;
			}
		}
	}

	// Get input, process it, and output the result
	effect->process();

	// Program finished
	return 0;
}

