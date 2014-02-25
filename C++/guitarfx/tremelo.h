// tremelo.h

#ifndef _TREMELO_H_
#define _TREMELO_H_

#include "audiofx.h"

class Tremelo : public AudioFX
{
public:
	//==================================================================
	Tremelo();
	
	//==================================================================
	void processSamples(BufferInfo* bufferToChange);
	int  paramSwitch(char param, float value);

private:
	//==================================================================
	float depth;
	float freq;
	float phase;
};

#endif // _TREMELO_H_

