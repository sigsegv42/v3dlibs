#ifndef INCLUDED_V3D_TGALOADER
#define INCLUDED_V3D_TGALOADER

#include "../ImageLoader.h"

namespace v3D
{

	class TGALoader : public ImageLoader
	{
		public:
			TGALoader();
			~TGALoader();

			virtual boost::shared_ptr<Image> load(const std::string & filename);
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_TGALOADER
