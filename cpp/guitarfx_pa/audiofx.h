// audiofx.h

#ifndef _AUDIOFX_H_
#define _AUDIOFX_H_

struct BufferInfo
{
	int sampleRate;
	int bufferSize;
	int numOfChannels;
	float** buffer;
};

class AudioFX
{
public:
	//==================================================================
	AudioFX();
	~AudioFX();

	//==================================================================
	void initialise(int sampleRate, int bufferSize, int numOfChannels);
	void process(float* bufferToProcess);
	void process();
	float* getBuffer();
	BufferInfo* getBufferInfo();

	//==================================================================
	virtual void processSamples(BufferInfo* bufferToChange)=0;
	virtual int  paramSwitch(char param, float value)=0;

private:
	//==================================================================
	BufferInfo buffer;
	float* ioBuffer;
};

#endif // _AUDIOFX_H_

