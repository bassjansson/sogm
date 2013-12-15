// reading, processing and writing a wav file (tremelo)

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double SAMPLERATE = 48000;
int HEADERSIZE = 44;
int BUFFERSIZE = 16;
int BYTEDEPTH = 2;
double ABSDEPTH = pow(2, BYTEDEPTH * 8 - 1);

char * header = new char[HEADERSIZE];
double * buffer = new double[BUFFERSIZE];

double depth = 1;
double freq = 300;
double phase = 0;

void readSamples(ifstream * file, int sample) {
	char * charbuffer = new char[BYTEDEPTH * BUFFERSIZE];

	file->seekg(sample);
	file->read(charbuffer, BYTEDEPTH * BUFFERSIZE);

	for(int i = 0; i < BUFFERSIZE; i++) {
		buffer[i] = 0;
		for(int r = 0; r < BYTEDEPTH; r++)
			buffer[i] += ((int)charbuffer[r + BYTEDEPTH * i] << r * 8);
		buffer[i] /= ABSDEPTH;
	}
}

void processSamples() {
	// tremelo 8 beats per second
	for(int i = 0; i < BUFFERSIZE; i++) {
	//	buffer[i] *= sin(phase) * depth/2 + 1 - depth/2;
		phase = fmod(phase + 2*M_PI * freq / SAMPLERATE, 2*M_PI);
	}
}

void writeSamples(ofstream * file, int sample) {
	char * charbuffer = new char[BYTEDEPTH * BUFFERSIZE];

	for(int i = 0; i < BUFFERSIZE; i++) {
		buffer[i] = round(buffer[i] * ABSDEPTH);
		for(int r = 0; r < BYTEDEPTH; r++)
			charbuffer[r + BYTEDEPTH * i] = (int)(((int)buffer[i] >> r * 8) & 0xFF);
	}
	file->seekp(sample);
	file->write(charbuffer, BYTEDEPTH * BUFFERSIZE);
}

int main (int argc, char* argv[]) {

	// Get inputfile
	ifstream inputfile;
	if(argc > 1) {
		inputfile.open(argv[1], ios::in|ios::binary|ios::ate);
	}
	else {
		clog << "No argument given for inputfile" << endl;
		delete[] header;
		delete[] buffer;
		return 0;
	}

	if(inputfile.is_open()) {
		// Get size of inputfile
    	ifstream::pos_type filesize = inputfile.tellg();
		// Create outputfile
		ofstream outputfile("./result.wav", ios::out|ios::binary|ios::beg);

		inputfile.seekg(0);
		inputfile.read(header, HEADERSIZE);
		outputfile.write(header, HEADERSIZE);

		for(int i = HEADERSIZE; i < filesize; i += BYTEDEPTH*BUFFERSIZE) {
			// Read Samples
			readSamples(&inputfile, i);
			// Process Samples
			processSamples();
			// Write Samples
			writeSamples(&outputfile, i);
		}

		inputfile.close();
		outputfile.close();

		cout << ABSDEPTH - 10001 << endl;
		double hai = (ABSDEPTH - 10001) / ABSDEPTH;
		cout << hai << endl;
		hai = round(hai * ABSDEPTH);
		cout << hai << endl;
		cout << filesize << endl;
	}
	else clog << "Failed to open " << argv[1] << endl;

	delete[] header;
	delete[] buffer;
	return 0;
}

