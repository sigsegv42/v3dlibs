#include "TGAReader.h"

#include <fstream>
#include <iostream>
#include <cstring>

using namespace v3D;

TGAReader::TGAReader()
{
}

TGAReader::~TGAReader()
{
}

boost::shared_ptr<Image> TGAReader::read(const std::string &filename)
{
	unsigned char TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};// Uncompressed TGA Header
	unsigned char TGAcompare[12];						// Used To Compare TGA Header
	unsigned char header[6];							// First 6 Useful Bytes From The Header

	std::fstream file;
	file.open(filename.c_str(), std::fstream::in | std::fstream::binary);
	boost::shared_ptr<Image> empty_ptr;
	if (file.fail())
	{
		return empty_ptr;
	}

	int length;
	file.seekg(0, std::fstream::end);
	length = file.tellg();
	file.seekg(0, std::fstream::beg);
	if (length < (sizeof(TGAcompare) + sizeof(header)))
	{
		file.close();
		return empty_ptr;
	}

	file.read(reinterpret_cast<char*>(&TGAcompare), sizeof(TGAcompare));
	if (memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0)
	{
		file.close();
		return empty_ptr;
	}

	file.read(reinterpret_cast<char*>(&header), sizeof(header));

	unsigned int width  = header[1] * 256 + header[0];	// Determine The TGA Width	(highbyte*256+lowbyte)
	unsigned int height = header[3] * 256 + header[2];	// Determine The TGA Height	(highbyte*256+lowbyte)
	unsigned int bpp = header[4];			// Grab The TGA's Bits Per Pixel (24 or 32)
    
 	if(width <= 0 ||						// Is The Width Less Than Or Equal To Zero
		height	<= 0 ||						// Is The Height Less Than Or Equal To Zero
		(header[4] != 24 && header[4] != 32))		// Is The TGA 24 or 32 Bit?
	{
		file.close();
		return empty_ptr;
	}

	boost::shared_ptr<Image> img(new Image(width, height, bpp));

	unsigned int bytespp = bpp / 8;
	unsigned int size = width * height * bytespp;
	unsigned char * data = img->data();
	file.read(reinterpret_cast<char*>(data), size);

	if (file.fail())
	{
		file.close();
		return empty_ptr;
	}

	unsigned int temp;
	for (unsigned int i = 0; i < int(size); i += bytespp)
	{										// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = temp;
	}
	file.close();
	return img;
}
