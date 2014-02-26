// chorus.h

#ifndef _CHORUS_H_
#define _CHORUS_H_

#include "audiofx.h"

class Chorus : public AudioFX
{
public:
	//==================================================================
	Chorus();
	~Chorus();
	
	//==================================================================
	void processSamples(BufferInfo* bufferToChange);
	int  paramSwitch(char param, float value);

private:
	//==================================================================
	float** history;
	int historySize;
	int historyPlace;

	float depth;
	float freq;
	float phase;
};

#endif // _CHORUS_H_

