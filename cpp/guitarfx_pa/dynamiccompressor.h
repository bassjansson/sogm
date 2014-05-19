// dynamiccompressor.h

#ifndef _DYNAMICCOMPRESSOR_H_
#define _DYNAMICCOMPRESSOR_H_

#include "audiofx.h"

class DynamicCompressor : public AudioFX
{
public:
	//==================================================================
	DynamicCompressor();
	~DynamicCompressor();
	
	//==================================================================
	void processSamples(BufferInfo* bufferToChange);
	int  paramSwitch(char param, float value);

private:
	//==================================================================
	float** history;
	int historySize;
	int historyPlace;

	float interval;
	float ratio;
	float* newRMS;
	float* oldRMS;
};

#endif // _DYNAMICCOMPRESSOR_H_

