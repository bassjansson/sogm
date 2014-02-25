// bitcrusher.h

#ifndef _BITCRUSHER_H_
#define _BITCRUSHER_H_

#include "audiofx.h"

class Bitcrusher : public AudioFX
{
public:
	//==================================================================
	Bitcrusher();

	//==================================================================
	void processSamples(BufferInfo* bufferToChange);
	int  paramSwitch(char param, float value);

private:
	//==================================================================
	int bitdepth;
	int rounding;
};

#endif // _BITCRUSHER_H_

