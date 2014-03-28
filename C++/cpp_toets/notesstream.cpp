
#include "notesstream.h"


NotesStream::NotesStream()
{
	notes = NULL;
	length = 0;
}

int NotesStream::readFile(char* fileName)
{
	ifstream inputFile(fileName);

	if(inputFile.is_open())
	{
		string line;
		getline(inputFile, line);
		length = getLength(line);
		notes = new Note[length];

		for(int i = 0; i < length; i++)
		{
			getline(inputFile, line);
			getNote(&notes[i], line);
		}

		inputFile.close();

		return 0;
	}
	else return 1;
}

int NotesStream::writeFile(char* fileName)
{
	ofstream outputFile(fileName);
	
	if(outputFile.is_open())
	{
		cout << "\"" << fileName << "\":\n\n";

		outputFile << length << ";\n";
		cout       << length << ";\n";

		for(int i = 0; i < length; i++)
		{
			outputFile << notes[i].pitch  << ";\t";
			outputFile << notes[i].attack << ";\t";
			outputFile << notes[i].decay  << ";";
			outputFile << endl;

			cout << notes[i].pitch  << ";\t";
			cout << notes[i].attack << ";\t";
			cout << notes[i].decay  << ";";
			cout << endl;
		}

		cout << endl;

		outputFile.close();

		return 0;
	}
	else return 1;
}

void NotesStream::modifyNotesForInstrument(Instrument* instrument)
{
	instrument->processNotes(notes, length);
}

int NotesStream::getLength(string firstLine)
{
	int number = 0;
	int offset = 0;

	return (int)getNextValue(firstLine, &number, &offset);
}

void NotesStream::getNote(Note* note, string line)
{
	int number = 0;
	int offset = 0;

	note->pitch  = getNextValue(line, &number, &offset);
	note->attack = getNextValue(line, &number, &offset);
	note->decay  = getNextValue(line, &number, &offset);
}

float NotesStream::getNextValue(string line, int* number, int* offset)
{
	while(line[*number] != ';') (*number)++;
	char* value = new char[*number - *offset];

	for(int i = *offset; i < *number; i++)
		value[i - *offset] = line[i];

	(*number)++;
	*offset = *number;

	return atof(value);
}

