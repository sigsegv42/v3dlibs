#ifndef INCLUDED_V3D_PNGLOADER
#define INCLUDED_V3D_PNGLOADER

#include "../ImageLoader.h"

namespace v3D
{

	class PNGLoader : public ImageLoader
	{
		public:
			PNGLoader();
			~PNGLoader();

			virtual boost::shared_ptr<Image> load(const std::string & filename);
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_PNGLOADER
