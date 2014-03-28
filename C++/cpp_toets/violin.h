
#ifndef _VIOLIN_H_
#define _VIOLIN_H_

#include "instrument.h"


class Violin : public Instrument
{
public:
	Violin();

protected:
	void getNewPitch  (float* pitch);
	void getNewAttack (float* attack);
	void getNewDecay  (float* decay);

private:
	float minPitch;
	float maxPitch;

	float minAttack;
	float maxAttack;

	float maxDecay;
};


#endif // _VIOLIN_H_

