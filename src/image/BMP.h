#ifndef INCLUDED_V3D_BMP_COMMON
#define INCLUDED_V3D_BMP_COMMON

namespace v3D
{

#pragma pack(push, 2)

	struct bmp_rgb_quad
	{
		unsigned char blue_;
		unsigned char green_;
		unsigned char red_;
		unsigned char reserved_;
	};

	struct bmp_info_header
	{
		unsigned long	size_;
		long			width_;
		long			height_;
		unsigned short	planes_;
		unsigned short	bits_;
		unsigned long	compression_;
		unsigned long	imageSize_;
		long			xppm_;
		long			yppm_;
		unsigned long	used_;
		unsigned long	important_;
	};

	struct bmp_file_header
	{
		unsigned short	type_;
		unsigned long	size_;
		unsigned short	reserved1_;
		unsigned short	reserved2_;
		unsigned long	offset_;
	};

#pragma pack(pop)

}; // end namespace v3D

#endif // INCLUDED_V3D_BMP_COMMON
