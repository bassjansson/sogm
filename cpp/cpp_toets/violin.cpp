
#include "violin.h"


Violin::Violin()
{
	minPitch = 55;  // midi
	maxPitch = 100; // midi

	minAttack = 20;   // ms
	maxAttack = 2000; // ms

	maxDecay = 5000; // ms
}

void Violin::getNewPitch(float* pitch)
{
	if(*pitch < minPitch)
		*pitch *= 2;
	else if(*pitch > maxPitch)
		*pitch /= 2;
}

void Violin::getNewAttack(float* attack)
{
	if(*attack < minAttack)
		*attack = minAttack;
	else if(*attack > maxAttack)
		*attack = maxAttack; 
}

void Violin::getNewDecay(float* decay)
{
	if(*decay > maxDecay)
		*decay = maxDecay;
}

