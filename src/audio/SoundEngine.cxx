#include "SoundEngine.h"

#include <iostream>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <boost/foreach.hpp>
#include <log4cxx/logger.h>


using namespace v3D;

SoundEngine::SoundEngine()
{
	// initialize OpenAL
	alutInit(0, 0);
	// clear any leftover error bits
	alGetError();

	// set listener properties
	updateListener();
}

SoundEngine::~SoundEngine()
{
}

void SoundEngine::shutdown(void)
{
	for (std::map<std::string, AudioClip>::iterator i = sounds_.begin(); i != sounds_.end(); i++)
	{
		(*i).second.destroy();
	}
	alutExit();
}

bool SoundEngine::load(const boost::property_tree::ptree & tree)
{
	std::string key, wav;
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("v3d.audio"));
	LOG4CXX_DEBUG(logger, "SoundEngine::load - looking for sound clips to load...");
	BOOST_FOREACH(boost::property_tree::ptree::value_type const & v, tree.get_child("config.sounds"))
	{
		if (v.first == "clip")
		{
			key = v.second.get<std::string>("<xmlattr>.id");
			wav = v.second.get<std::string>("<xmlattr>.file");
			loadClip(wav, key);
		}
	}
	return true;
}

bool SoundEngine::loadClip(const std::string & filename, const std::string & key)
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("v3d.audio"));
	LOG4CXX_DEBUG(logger, "SoundEngine::loadClip - loading audio clip with filename [" << filename << "] with id [" << key << "]");

	AudioClip clip;

	clip.load(filename);
	sounds_[key] = clip;

	return true;
}

void SoundEngine::playClip(const std::string & clip)
{
	if (sounds_.find(clip) == sounds_.end())
		return;

	alSourcePlay(sounds_[clip].source());
}

void SoundEngine::updateListener(void)
{
	alListenerfv(AL_POSITION, *listenerPosition_);
	alListenerfv(AL_VELOCITY, *listenerVelocity_);

	ALfloat listenerOrientation[] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };
	alListenerfv(AL_ORIENTATION, listenerOrientation);
}
