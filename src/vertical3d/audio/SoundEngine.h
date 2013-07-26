#ifndef INCLUDED_V3D_SOUNDENGINE
#define INCLUDED_V3D_SOUNDENGINE

#include "AudioClip.h"

#include <boost/property_tree/ptree.hpp>
#include <map>

namespace v3D
{

	/**
	 * The SoundEngine class. It is responsible for all of the OpenAL functionality. 
	 **/
	class SoundEngine
	{
		public:
			SoundEngine();
			~SoundEngine();

			void shutdown();
			bool load(const boost::property_tree::ptree & tree, const std::string & assetPath);
			bool loadClip(const std::string & filename, const std::string & key);
			bool playClip(const std::string & clip);
			void updateListener();

		private:
			std::map<std::string, AudioClip> sounds_;

			Vector3 listenerPosition_;
			Vector3 listenerVelocity_;
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_SOUNDENGINE
