
#include "instrument.h"


void Instrument::processNotes(Note* notes, int length)
{
	for(int i = 0; i < length; i++)
	{
		getNewPitch  (&notes[i].pitch);
		getNewAttack (&notes[i].attack);
		getNewDecay  (&notes[i].decay);
	}
}

