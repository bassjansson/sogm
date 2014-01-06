// reading, processing and writing a wav file (tremelo)

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define BYTEDEPTH 2
#define HEADERSIZE 44
#define SAMPLERATE 48000
#define ABSDEPTH 32767

int DELAYSIZE = 0;
int BLOCKSIZE = 1024;
int BUFFERSIZE = DELAYSIZE + BLOCKSIZE;

double * block = new double[BLOCKSIZE];
double * buffer = new double[BUFFERSIZE];

double depth = 1;
double freq = 10;
double phase = 0;

void readSample(ifstream * file, int sampleblock) {
	short * shortbuffer = new short[BLOCKSIZE];

	file->seekg(sampleblock * BLOCKSIZE * BYTEDEPTH + HEADERSIZE);
	file->read((char*)shortbuffer, BLOCKSIZE * BYTEDEPTH);

	for(int i = 0; i < DELAYSIZE; i++) {
		buffer[i] = buffer[i + BLOCKSIZE];
	}

	for(int i = 0; i < BLOCKSIZE; i++) {
		buffer[i + DELAYSIZE] = (double)shortbuffer[i] / ABSDEPTH;
	}
}

void processSample(int sampleblock) {
	// tremelo 8 beats per second
	for(int i = 0; i < BLOCKSIZE; i++) {
		block[i] = buffer[i + DELAYSIZE] * (sin(phase) * depth/2 + 1 - depth/2);
		phase = fmod(phase + 2*M_PI * freq / SAMPLERATE, 2*M_PI);
	}
}

void writeSample(ofstream * file, int sampleblock) {
	short * shortbuffer = new short[BLOCKSIZE]; 
	
	for(int i = 0; i < BLOCKSIZE; i++) {
		shortbuffer[i] = round(block[i] * ABSDEPTH);;
	}

	file->seekp(sampleblock * BLOCKSIZE * BYTEDEPTH + HEADERSIZE);
	file->write((char*)shortbuffer, BLOCKSIZE * BYTEDEPTH);
}

int main (int argc, char* argv[]) {

	// Get inputfile
	ifstream inputfile;
	if(argc > 1) {
		inputfile.open(argv[1], ios::in|ios::binary|ios::ate);
	}
	else {
		clog << "No argument given for inputfile, program stopped" << endl;
		delete[] buffer;
		return 0;
	}

	if(inputfile.is_open()) {
		// Get size of inputfile
    	ifstream::pos_type filesize = inputfile.tellg();
		filesize = ((int)filesize - HEADERSIZE) / BYTEDEPTH / BLOCKSIZE;

		// Go to the start of file and read header
		inputfile.seekg(0);
		char * header = new char[HEADERSIZE];
		inputfile.read(header, HEADERSIZE);

		// Check if input channels are greater than one and stop if true
		/*if((int)header[22] > 1) {
			cout << "Number of channels is more than one, program stopped" << endl;
			inputfile.close();
			delete[] header;
			delete[] buffer;
			return 0;
		}*/

		// Create outputfile and write header
		ofstream outputfile("./result.wav", ios::out|ios::binary|ios::beg);
		outputfile.write(header, HEADERSIZE);
		delete[] header;

		for(int s = 0; s < filesize; s++) {
			// Read Samples
			readSample(&inputfile, s);
			// Process Samples
			processSample(s);
			// Write Samples
			writeSample(&outputfile, s);
		}

		inputfile.close();
		outputfile.close();
	}
	else clog << "Failed to open " << argv[1] << ", program stopped" << endl;

	delete[] buffer;
	return 0;
}

