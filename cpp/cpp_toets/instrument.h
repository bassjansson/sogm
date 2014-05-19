
#ifndef _INSTRUMENT_H_
#define _INSTRUMENT_H_


struct Note
{
	float pitch;  // midi
	float attack; // ms
	float decay;  // ms
};


class Instrument
{
public:	
	void processNotes(Note* notes, int length);

protected:
	virtual void getNewPitch  (float* pitch)  = 0;
	virtual void getNewAttack (float* attack) = 0;
	virtual void getNewDecay  (float* decay)  = 0;
};


#endif // _INSTRUMENT_H_

