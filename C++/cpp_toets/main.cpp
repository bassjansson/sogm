
#include <iostream>

#include "notesstream.h"

#include "guitar.h"
#include "violin.h"

using namespace std;

#define INPUT  1
#define OUTPUT 2


int main(int argc, char* argv[])
{
	// Check if enough arguments are given
	if(argc < 3)
	{
		// Give manual
		cout << "Give file to read from and file to write to. Example:\n\n";
		cout << "\tcpp_toets files/input.txt files/output.txt\n\n";

		// Program failed with error 1
		return 1;
	}
	else
	{
		// Create notes file stream
		NotesStream notesStream;

		// Read input file and check if succeeded
		if(notesStream.readFile(argv[INPUT]) != 0)
		{
			// The input file couldn't be read
			cout << "Couldn't read the file \"" << argv[INPUT] << "\".\n\n";
			
			// Program failed with error 2
			return 2;
		}
		else
		{
			// Create instrument
			Instrument* instrument;
			int instrumentNumber;
		
			// Let the user choose the instrument
			cout << "Instruments:\n";
			cout << "\t- Guitar (1) (default)\n";
			cout << "\t- Violin (2)\n\n";
			cout << "Give instrument number: ";
			cin >> instrumentNumber;
			cout << endl;
		
			// Switch chosen instrument
			switch(instrumentNumber)
			{
				default: instrument = new Guitar(); break;

				case 1:  instrument = new Guitar(); break;
				case 2:  instrument = new Violin(); break;
			}

			// Modify notes for instrument
			notesStream.modifyNotesForInstrument(instrument);
			
			// Write output file and check if succeeded
			if(notesStream.writeFile(argv[OUTPUT]) != 0)
			{
				// The output file couldn't be written
				cout << "Couldn't write the file \"" << argv[OUTPUT] << "\".\n\n";

				// Program failed with error 2
				return 2;
			}
			else
			{
				// Program succeeded
				return 0;
			}
		}
	}
}

