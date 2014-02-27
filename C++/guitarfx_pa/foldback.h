// foldback.h

#ifndef _FOLDBACK_H_
#define _FOLDBACK_H_

#include "audiofx.h"

class Foldback : public AudioFX
{
public:
	//==================================================================
	Foldback();

	//==================================================================
	void processSamples(BufferInfo* bufferToChange);
	int  paramSwitch(char param, float value);

private:
	//==================================================================
	float drive;
};

#endif // _FOLDBACK_H_

