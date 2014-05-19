// amplifier.h

#ifndef _AMPLIFIER_H_
#define _AMPLIFIER_H_

#include "audiofx.h"

class Amplifier : public AudioFX
{
public:
	//==================================================================
	Amplifier();

	//==================================================================
    void processSamples(BufferInfo* bufferToChange);
	int  paramSwitch(char param, float value);

private:
	//==================================================================
	float gain;
};

#endif // _AMPLIFIER_H_

