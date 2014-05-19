
#include "guitar.h"
#include <cmath>


Guitar::Guitar()
{
	minPitch = 40; // midi
	maxPitch = 88; // midi
	
	guitarAttack = 20; // ms

	maxDecay = 10000; // ms
}

void Guitar::getNewPitch(float* pitch)
{
	*pitch = int(roundf(*pitch));

	if(*pitch < minPitch)
		*pitch *= 2;
	else if(*pitch > maxPitch)
		*pitch /= 2;
}

void Guitar::getNewAttack(float* attack)
{
	*attack = guitarAttack; 
}

void Guitar::getNewDecay(float* decay)
{
	if(*decay > maxDecay)
		*decay = maxDecay;
}

