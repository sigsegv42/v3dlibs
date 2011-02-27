#include "BMPLoader.h"
#include "../ImageFactory.h"

#include <fstream>

using namespace v3D;

struct bmp_rgb_quad
{
	unsigned char _blue;
	unsigned char _green;
	unsigned char _red;
	unsigned char _reserved;
};

struct bmp_info_header
{
	unsigned long	_size;
	long			_width;
	long			_height;
	unsigned short	_planes;
	unsigned short	_bits;
	unsigned long	_compression;
	unsigned long	_imageSize;
	long			_xppm;
	long			_yppm;
	unsigned long	_used;
	unsigned long	_important;
};

struct bmp_file_header
{
	unsigned short	_type;
	unsigned long	_size;
	unsigned short	_reserved1;
	unsigned short	_reserved2;
	unsigned long	_offset;
};

BMPLoader::BMPLoader()
{
}

BMPLoader::~BMPLoader()
{
}

boost::shared_ptr<Image> BMPLoader::load(const std::string & filename)
{
	std::fstream file;
	file.open(filename.c_str(), std::fstream::in | std::fstream::binary);

	boost::shared_ptr<Image> empty_ptr;

	if (file.fail())
		return empty_ptr;

	bmp_file_header fheader;

	// read file header
	file.read(reinterpret_cast<char*>(&fheader), sizeof(bmp_file_header));

	// check magic number
	if (fheader._type != 19778)
		return empty_ptr;

	bmp_info_header iheader;

	// read info header
	file.read(reinterpret_cast<char*>(&iheader), sizeof(bmp_info_header));

	int num_colors = 1 << iheader._bits;

	bmp_rgb_quad * colors = 0;
	if (iheader._bits == 8) // load 8 bit color palette
	{
		colors = new bmp_rgb_quad[num_colors];
		file.read(reinterpret_cast<char*>(&colors), sizeof(bmp_rgb_quad) * num_colors);
	}

	// size of image data buffer including boundary padding
	unsigned long size = iheader._width * iheader._height * (iheader._bits / 8);
	// this is just temporary storage
	boost::shared_ptr<Image> img(new Image(size));
	unsigned char * temp = img->data();
	// read image data
	file.read(reinterpret_cast<char*>(&temp), size);

	// done reading in file
	file.close();

	long width, pad;
	width = pad = iheader._width * (iheader._bits / 8);
	// adjust pad width to dword boundary alignment
	while (pad % 4 != 0)
	{
		pad++;
	}

	int offset = pad - width;
	unsigned long height = iheader._height;

	boost::shared_ptr<Image> image(new Image(iheader._width, height, 24));
	unsigned char * data = image->data();

	
	// convert 8/24bit image from bgr to rgb
	if (iheader._bits == 8)
	{
		//diff = iheader._width * iheader._height * 3;
	    //allocate the buffer for the final image data
		//data = new char[diff];

		if (iheader._height > 0) 
		{
			int j = 0;
			//count backwards so you start at the front of the image
		    for (unsigned int i = 0; i < size * 3; i += 3) 
			{
				//jump over the padding at the start of a new line
				if((i + 1) % pad == 0) 
				{
					i += offset;
				}
	            //transfer the data
		        *(data + i) = colors[*(temp + j)]._red;
			    *(data + i + 1) = colors[*(temp + j)]._green;
				*(data + i + 2) = colors[*(temp + j)]._blue;
				j++;
			}
		} 
		else //image parser for a forward image
		{
		    int j = size - 1;
			//count backwards so you start at the front of the image
	        for (unsigned int i = 0; i < size * 3; i += 3) 
			{
				//jump over the padding at the start of a new line
				if ((i + 1) % pad == 0) 
				{
					i += offset;
				}
				//transfer the data
			    *(data + i) = colors[*(temp + j)]._red;
				*(data + i + 1) = colors[*(temp + j)]._green;
				*(data + i + 2) = colors[*(temp + j)]._blue;
				j--;
			}
		}
	}
	else if (iheader._bits == 24)
	{
		if(iheader._height > 0) 
		{
		    //count backwards so you start at the front of the image
	        for(unsigned int i = 0; i < size; i += 3) 
			{
				//jump over the padding at the start of a new line
			    if((i + 1) % pad == 0) 
				{
					i+=offset;
				}

				//transfer the data
				*(data + i + 2) = *(temp + i);
			    *(data + i + 1) = *(temp + i + 1);
				*(data + i) = *(temp + i + 2);
			}
	    }
		else //image parser for a forward image
		{
			int j = size - 3;
			//count backwards so you start at the front of the image
			//here you can start from the back of the file or the front,
			//after the header  The only problem is that some programs
			//will pad not only the data, but also the file size to
			//be divisible by 4 bytes.
			for(unsigned int i = 0; i < size; i += 3) 
			{
	           //jump over the padding at the start of a new line
				if((i + 1) % pad == 0) 
				{
	                i += offset;
		        }
	            //transfer the data
		        *(data + j + 2) = *(temp + i);
			    *(data + j + 1) = *(temp + i + 1);
				*(data + j) = *(temp + i + 2);
	            j -= 3;
		    }
		}
	}
	else
	{
		throw std::string("unrecognized bmp bits!");
	}
	return image;
}
