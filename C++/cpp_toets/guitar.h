
#ifndef _GUITAR_H_
#define _GUITAR_H_

#include "instrument.h"


class Guitar : public Instrument
{
public:
	Guitar();

protected:
	void getNewPitch  (float* pitch);
	void getNewAttack (float* attack);
	void getNewDecay  (float* decay);

private:
	float minPitch;
	float maxPitch;

	float guitarAttack;

	float maxDecay;
};


#endif // _GUITAR_H_

