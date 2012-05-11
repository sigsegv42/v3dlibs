#include "AudioClip.h"

#include <iostream>

#ifdef WIN32
#include <al.h>
#include <alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif
#include <AL/alut.h>

using namespace v3D;

AudioClip::AudioClip()
{
}

AudioClip::~AudioClip()
{
}

unsigned int AudioClip::source(void) const
{
	return source_;
}

void AudioClip::destroy(void)
{
	alDeleteBuffers(1, &buffer_);
	alDeleteSources(1, &source_);
}

bool AudioClip::load(const std::string & filename)
{
	ALboolean loop = false;

	// load sound data from file
	buffer_ = alutCreateBufferFromFile(filename.c_str());
	if (alGetError() != AL_NO_ERROR)
	{
		std::cerr << "alut create failed" << std::endl;
		return false;
	}

	// create a source for the sound
	alGenSources(1, &source_);
	if (alGetError() != AL_NO_ERROR)
	{
		std::cerr << "error generating OpenAL sources" << std::endl;
		return false;
	}

	// link the sound buffer to the source
	alSourcei(source_, AL_BUFFER, buffer_);
	// and set the source properties
	alSourcef(source_, AL_PITCH, 1.0f);
	alSourcef(source_, AL_GAIN, 1.0f);
	/* these next two set an error bit...
	alSourcefv(_source, AL_POSITION, _position.raw());
	alSourcefv(_source, AL_VELOCITY, _velocity.raw());
	*/
	alSourcei(source_, AL_LOOPING, loop);

	if (alGetError() != AL_NO_ERROR)
	{
		std::cerr << "error setting source properties" << std::endl;
		return false;
	}

	return true;
}

