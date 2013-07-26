#ifndef INCLUDED_V3D_AUDIOCLIP
#define INCLUDED_V3D_AUDIOCLIP

#include "../3dtypes/Vector3.h"

#include <string>

namespace v3D
{

	class AudioClip
	{
		public:
			AudioClip();
			~AudioClip();

			bool load(const std::string & filename);
			void destroy();

	//		unsigned int buffer(void) const;
			unsigned int source() const;

	//		vector3d position(void) const;
	//		vector3d velocity(void) const;

		private:
			unsigned int buffer_;
			unsigned int source_;

			Vector3 position_;
			Vector3 velocity_;
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_AUDIOCLIP
