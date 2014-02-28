// dynamicinverter.h

#ifndef _DYNAMICINVERTER_H_
#define _DYNAMICINVERTER_H_

#include "audiofx.h"

class DynamicInverter : public AudioFX
{
public:
	//==================================================================
	DynamicInverter();
	~DynamicInverter();
	
	//==================================================================
	void processSamples(BufferInfo* bufferToChange);
	int  paramSwitch(char param, float value);

private:
	//==================================================================
	float** history;
	int historySize;
	int historyPlace;

	float interval;
	float* newRMS;
	float* oldRMS;
};

#endif // _DYNAMICINVERTER_H_

