// audiofx.cpp

#include "audiofx.h"

AudioFX::AudioFX(int buffer_size)
{
	setMode(AUDIO_IO_READWRITE);

	this->buffer_place = 0;
	this->buffer_size = buffer_size;
	this->buffer = new float[buffer_size];
}

AudioFX::~AudioFX()
{
	buffer = nullptr;
}


void AudioFX::setAudioSettings(int samplerate, int frame_size, int channels)
{
	set_samplerate(samplerate);
	set_framesperbuffer(frame_size);
	set_nrofchannels(channels);
}

void AudioFX::startAudio()
{
	initialise();
	list_devices();
	int device;

	cout << "\nGive input device number: ";
	cin >> device;
	set_input_device(device);

	cout << "\nGive output device number: ";
	cin >> device;
	set_output_device(device);

	start_server();
}

void AudioFX::stopAudio()
{
	finalise();
}

void AudioFX::process()
{
	read(buffer + buffer_place);
	processSamples(framesperbuffer, nrofchannels);
	write(buffer + buffer_place);
	buffer_place = (buffer_place + framesperbuffer * nrofchannels) % buffer_size;
}

int AudioFX::getSamplePlace(int sample, int channel)
{
	return (sample * nrofchannels + channel + buffer_size + buffer_place) % buffer_size;
}


void AudioFX::processSamples(int frame_size, int channels)
{
	for(int s = 0; s < frame_size; s++) {
		for(int c = 0; c < channels; c++) {
			// Audio Processing Goes Here
		}
	}
}

int AudioFX::paramSwitch(char param, float value)
{
	return 0;
}

