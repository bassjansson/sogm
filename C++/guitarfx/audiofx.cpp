// audiofx.cpp

#include "audiofx.h"

//==================================================================
AudioFX::AudioFX()
{
	// Default settings
	buffer.sampleRate	 = 48000;
	buffer.bufferSize	 = 256;
	buffer.numOfChannels = 1;

	ioBuffer = new float[buffer.bufferSize * buffer.numOfChannels];

	buffer.buffer = new float*[buffer.numOfChannels];
	for(int c = 0; c < buffer.numOfChannels; c++)
		buffer.buffer[c] = ioBuffer + long(buffer.bufferSize * c);
}

AudioFX::~AudioFX()
{
	delete buffer.buffer;
	delete ioBuffer;
}

//==================================================================
void AudioFX::initialise(int sampleRate, int bufferSize, int numOfChannels)
{
	buffer.sampleRate	 = sampleRate;
	buffer.bufferSize	 = bufferSize;
	buffer.numOfChannels = numOfChannels;

	ioBuffer = new float[buffer.bufferSize * buffer.numOfChannels];

	buffer.buffer = new float*[buffer.numOfChannels];
	for(int c = 0; c < buffer.numOfChannels; c++)
		buffer.buffer[c] = ioBuffer + long(buffer.bufferSize * c);
}

void AudioFX::process(float* bufferToProcess)
{
	// Remap buffer
	ioBuffer = bufferToProcess;

	for(int c = 0; c < buffer.numOfChannels; c++)
		buffer.buffer[c] = ioBuffer + long(buffer.bufferSize * c);

	// Process samples
	processSamples(&buffer);

	// Clip processed samples
	for(int c = 0; c < buffer.numOfChannels; c++)
	{
		for(int s = 0; s < buffer.bufferSize; s++)
		{
			if      (buffer.buffer[c][s] >  1.0f) buffer.buffer[c][s] =  1.0f;
			else if (buffer.buffer[c][s] < -1.0f) buffer.buffer[c][s] = -1.0f;
		}
	}
}

void AudioFX::process()
{
	// Process samples
	processSamples(&buffer);

	// Clip processed samples
	for(int c = 0; c < buffer.numOfChannels; c++)
	{
		for(int s = 0; s < buffer.bufferSize; s++)
		{
			if      (buffer.buffer[c][s] >  1.0f) buffer.buffer[c][s] =  1.0f;
			else if (buffer.buffer[c][s] < -1.0f) buffer.buffer[c][s] = -1.0f;
		}
	}
}

float* AudioFX::getBuffer()
{
	return ioBuffer;
}

BufferInfo* AudioFX::getBufferInfo()
{
	return &buffer;
}

