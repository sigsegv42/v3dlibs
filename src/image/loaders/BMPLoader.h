#ifndef INCLUDED_V3D_BMPLOADER
#define INCLUDED_V3D_BMPLOADER

#include "../ImageLoader.h"

namespace v3D
{

	class BMPLoader : public ImageLoader
	{
		public:
			BMPLoader();
			~BMPLoader();

			virtual boost::shared_ptr<Image> load(const std::string & filename);
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_BMPLOADER
