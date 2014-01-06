// audiofx.cpp

#include "audiofx.h"

// Members which can't be modified
AudioFX::AudioFX(int blocksize) {
    this->blocksize = blocksize;
    this->buffersize = blocksize * 4;

	buffer = new double * [5];
    for(int i = 0; i < MAXCHANNELS; i++) buffer[i] = new double[buffersize];
    header = new char[HEADERSIZE];
}

AudioFX::~AudioFX() {
	delete[] buffer;
    delete[] header;

    inputfile.close();
    outputfile.close();
}



bool AudioFX::openFile(char * filename) {
    // Open file
    inputfile.open(filename, ios::in|ios::binary|ios::ate);

    if(inputfile.is_open()) {
        // Get filesize, go to first byte, get header and get channels
        // Return true if file open succeeded
        filesize = ((int)inputfile.tellg() - HEADERSIZE) / BYTEDEPTH;
        inputfile.seekg(0);
        inputfile.read(header, HEADERSIZE);
        channels = (int)header[22];
        return true;
    }
    else {
        // Return false if file open failed
        return false;
    }
}

bool AudioFX::createFile(char * filename) {
    // Open file
    outputfile.open(filename, ios::out|ios::binary|ios::beg);
	
    if(outputfile.is_open()) {
        // Write header
        // Return true if file open succeeded
        outputfile.write(header, HEADERSIZE);
        return true;
    }
    else {
        // Return false if file open failed
        return false;
    }
}



void AudioFX::circulate(int block) {
    history    = ( block      % 3) * blocksize;
    processing = ((block + 1) % 3) * blocksize;
    reading    = ((block + 2) % 3) * blocksize;
    writing    = 3 * blocksize;
}

void AudioFX::readSamples(ifstream * file, int block) {
    short shortbuffer[blocksize * channels];
    int byteblocksize = blocksize * channels * BYTEDEPTH;

    file->seekg(block * byteblocksize + HEADERSIZE);
	file->read((char*)shortbuffer, byteblocksize);

    for(int c = 0; c < channels; c++) {
	    for(int i = 0; i < blocksize; i++) {	
            buffer[c][i + reading] = (double)shortbuffer[i * channels + c] / ABSDEPTH;
        }
	}
}

void AudioFX::writeSamples(ofstream * file, int block) {
	short shortbuffer[blocksize * channels];
    int byteblocksize = blocksize * channels * BYTEDEPTH;
	
    for(int c = 0; c < channels; c++) {
    	for(int i = 0; i < blocksize; i++) {
            shortbuffer[i * channels + c] = round(buffer[c][i + writing] * ABSDEPTH);
	    }
    }

	file->seekp((block - 1) * byteblocksize + HEADERSIZE);
	file->write((char*)shortbuffer, byteblocksize);
}



// Members which can be modified by a derived class
void AudioFX::processSamples() {
    for(int c = 0; c < channels; c++) {
        for(int i = 0; i < blocksize; i++) {
            buffer[c][i + writing] = buffer[c][i + processing];
        }
    }
}

void AudioFX::process() {
    circulate(0);
    readSamples(&inputfile, 0);

    for(int i = 1; i < filesize / blocksize + 2; i++) {
        circulate(i);
        readSamples(&inputfile, i);
        processSamples();
        writeSamples(&outputfile, i);
    }
}

int AudioFX::paramSwitch(char param, float value) {
	return 0;
}



/*
    Use of a circular buffer, but writing stays on it's place:

        %3        +1%3        +2%3        3
    | history | processing | reading | writing |

    blocksize = size of each of the 4 blocks
    buffersize = size of all 4 blocks together
*/

