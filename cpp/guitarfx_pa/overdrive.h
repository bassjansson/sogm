// overdrive.h

#ifndef _OVERDRIVE_H_
#define _OVERDRIVE_H_

#include "audiofx.h"

class Overdrive : public AudioFX
{
public:
	//==================================================================
	Overdrive();

	//==================================================================
	void processSamples(BufferInfo* bufferToChange);
	int  paramSwitch(char param, float value);

private:
	//==================================================================
	float drive;
};

#endif // _OVERDRIVE_H_

