
#ifndef _NOTESSTREAM_H_
#define _NOTESSTREAM_H_

#include <iostream>
#include <fstream>
#include <string>

#include "instrument.h"

using namespace std;


class NotesStream
{
public:
	NotesStream();

	int readFile  (char* fileName);
	int writeFile (char* fileName);

	void modifyNotesForInstrument(Instrument* instrument);

private:
	Note* notes;
	int length;

	int   getLength    (string firstLine);
	void  getNote      (Note* note, string line);
	float getNextValue (string line, int* number, int* offset);
};


#endif // _NOTESSTREAM_H_

