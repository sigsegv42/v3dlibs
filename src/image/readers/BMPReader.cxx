#include "BMPReader.h"
#include "../BMP.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace v3D;


BMPReader::BMPReader()
{
}

BMPReader::~BMPReader()
{
}

void debug_file_header(const bmp_file_header & fheader)
{
	std::cout << "bmp type: " << fheader.type_ << std::endl;
	std::cout << "bmp size: " << fheader.size_ << std::endl;
	std::cout << "bmp reserved1: " << fheader.reserved1_ << std::endl;
	std::cout << "bmp reserved2: " << fheader.reserved2_ << std::endl;
	std::cout << "bmp offset: " << fheader.offset_ << std::endl;
}

void debug_info_header(const bmp_info_header & iheader)
{
	std::cout << "info size: " << iheader.size_ << std::endl;
	std::cout << "info width: " << iheader.width_ << std::endl;
	std::cout << "info height: " << iheader.height_ << std::endl;
	std::cout << "info planes: " << iheader.planes_ << std::endl;
	std::cout << "info bits: " << iheader.bits_ << std::endl;
	std::cout << "info compression: " << iheader.compression_ << std::endl;
	std::cout << "info image size: " << iheader.imageSize_ << std::endl;
	std::cout << "info xppm: " << iheader.xppm_ << std::endl;
	std::cout << "info yppm: " << iheader.yppm_ << std::endl;
	std::cout << "info used: " << iheader.used_ << std::endl;
	std::cout << "info important: " << iheader.important_ << std::endl;
}

boost::shared_ptr<Image> BMPReader::read(const std::string & filename)
{
	bool debug = false;

	std::fstream file;
	file.open(filename.c_str(), std::fstream::in | std::fstream::binary);

	boost::shared_ptr<Image> empty_ptr;

	if (!file)
	{
		return empty_ptr;
	}

	bmp_file_header fheader;
	memset(&fheader, 0, sizeof(bmp_file_header));

	// read file header
	file.read(reinterpret_cast<char*>(&fheader), sizeof(bmp_file_header));
	if (!file)
	{
		throw std::string("error reading bmp file header!");
	}

	// check magic number
	if (fheader.type_ != 19778)
	{
		return empty_ptr;
	}

	bmp_info_header iheader;
	memset(&iheader, 0, sizeof(bmp_info_header));

	// read info header
	file.read(reinterpret_cast<char*>(&iheader), sizeof(bmp_info_header));
	if (!file)
	{
		throw std::string("error reading bmp info header!");
	}

	int num_colors = 1 << iheader.bits_;

	if (debug)
	{
		debug_file_header(fheader);
		debug_info_header(iheader);
		std::cout << "num colors: " << num_colors << std::endl;
	}

	bmp_rgb_quad * colors = 0;
	if (iheader.bits_ == 8) // load 8 bit color palette
	{
		colors = new bmp_rgb_quad[num_colors];
		file.read(reinterpret_cast<char*>(&colors), sizeof(bmp_rgb_quad) * num_colors);
	}

	if (!file)
	{
		throw std::string("error reading bmp colors!");
	}
	// size of image data buffer including boundary padding
	unsigned long size = iheader.width_ * iheader.height_ * (iheader.bits_ / 8);
	long width, pad;
	width = pad = iheader.width_ * (iheader.bits_ / 8);
	// adjust pad width to dword boundary alignment
	while (pad % 4 != 0)
	{
		pad++;
	}
	if (debug)
	{
		std::cout << "allocating image bits: " << size << std::endl;
		std::cout << "width is: " << width << " after padding: " << pad << std::endl;
	}

	// this is just temporary storage
	boost::shared_ptr<Image> img(new Image(size));
	unsigned char * temp = img->data();
	if (debug)
	{
		int pos = file.tellg();
		file.seekg(0, std::ios::end);
		int length = file.tellg();
		file.seekg(pos, std::ios::beg);
		std::cout << "file pointer: " << file.tellg() << std::endl;
		std::cout << "file length: " << length << std::endl;
	}
	// read image data
	file.read(reinterpret_cast<char*>(temp), size);

	if (debug)
	{
		std::cout << "done reading file.." << std::endl;
	}
	if (!file)
	{
		throw std::string("error reading bmp data!");
	}

	// done reading in file
	file.close();

	int offset = pad - width;
	unsigned long height = iheader.height_;

	boost::shared_ptr<Image> image(new Image(iheader.width_, height, 24));
	unsigned char * data = image->data();

	// convert 8/24bit image from bgr to rgb
	if (iheader.bits_ == 8)
	{
		//diff = iheader._width * iheader._height * 3;
	    //allocate the buffer for the final image data
		//data = new char[diff];

		if (iheader.height_ > 0) 
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
		        *(data + i) = colors[*(temp + j)].red_;
			    *(data + i + 1) = colors[*(temp + j)].green_;
				*(data + i + 2) = colors[*(temp + j)].blue_;
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
			    *(data + i) = colors[*(temp + j)].red_;
				*(data + i + 1) = colors[*(temp + j)].green_;
				*(data + i + 2) = colors[*(temp + j)].blue_;
				j--;
			}
		}
		delete [] colors;
	}
	else if (iheader.bits_ == 16)
	{
		for (unsigned int i = 0; i < size; i += 2)
		{
			//jump over the padding at the start of a new line
		    if((i + 1) % pad == 0) 
			{
				i += offset;
			}
			// 0123 4567 0123 4567
			// 1234 5678 1234 5678
			// RRRR RGGG GGBB BBB0
			*(data + i) = ((*(temp + i) >> 3) << 3); // R
			*(data + i + 1) = (*(temp + i) << 5) | ((*(temp + i + 1) >> 6) << 6); // G
			*(data + i + 2) = ((*(temp + i + 1) >> 1) << 3); // B
		}
	}
	else if (iheader.bits_ == 24)
	{
		if(iheader.height_ > 0) 
		{
		    //count backwards so you start at the front of the image
	        for(unsigned int i = 0; i < size; i += 3) 
			{
				//jump over the padding at the start of a new line
			    if((i + 1) % pad == 0) 
				{
					i += offset;
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
		std::stringstream ss;
		ss << iheader.bits_;
		throw std::string("unrecognized bmp bits - " + ss.str() + "!");
	}
	return image;
}
