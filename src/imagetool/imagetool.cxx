/**
 * image manipulation tool
 * (c) 2008 Joshua Farr
 * 
 * TODO:
 * (*) main
 * (*) getopt
 * (*) usage
 * (*) determine filetype from filename extension
 * (*) display image info
 * (*) verify reading bmp works properly by writing bmp after reading
 * (*) read 24bit tga
 * (*) read jpeg
 * (*) write jpeg
 * (*) write bmp
 *		(*) write 24bit bmp
 *		(*) write 32bit bmp
 * ( ) write tga
 *		(*) write 24 bit tga
 *		( ) write 24 bit rle tga
 * ( ) read bmp
 *		( ) read 8 bit bmp
 *		( ) read 16 bit bmp
 *		(*) read 24 bit bmp
 *		( ) read 32 bit bmp
 * (*) read png
 *		(*) read 32 bit png
 * (*) write png
 */

#include <iostream>

#include "../util/getopts.h"
#include "../image/ImageFactory.h"

void usage(void)
{
	std::cout << "usage:" << std::endl;
	std::cout << "imagetool --file filename --outfile filename --info --silent" << std::endl;
	std::cout << "	--info		- display image info" << std::endl;
	std::cout << "	--silent	- don't display any output" << std::endl;
	std::cout << "	--file		- input image filename to be read" << std::endl;
	std::cout << "	--outfile	- image filename to be written" << std::endl;
}

int main (int argc, char *argv[])
{

	GetOpts getopts(argc, argv, "i|info:s|silent:f|file*:o|outfile*");

	bool info = false;
	bool silent = false;
	bool sync = false;
	std::string infile;
	std::string outfile;

	int opt;
	while ((opt = getopts.next()) != EOF)
	{
		switch (opt)
		{
			case 'i':
				info = true;
				break;
			case 's':
				silent = true;
				break;
			case 'f':
				infile = getopts.getarg();
				break;
			case 'o':
				sync = true;
				outfile = getopts.getarg();
				break;
			default:
				break;
		}
	}

	if (infile.empty())
	{
		usage();
		exit(EXIT_SUCCESS);
	}

	v3D::ImageFactory factory;
	boost::shared_ptr<v3D::Image> image;

	if (!silent)
	{
		std::cout << "Reading: " << infile << std::endl;
		try
		{
			image = factory.read(infile);
		}
		catch (std::string & e)
		{
			std::cout << "error reading image! - " << e << std::endl;
			exit(EXIT_FAILURE);
		}
		if (!image)
		{
			std::cout << "error reading file!" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	if (info)
	{
		std::cout << "Source image width: " << image->width() << std::endl;
		std::cout << "Source image height: " << image->height() << std::endl;
		std::cout << "Source image bpp: " << image->bpp() << std::endl;
	}

	if (sync)
	{
		std::cout << "Writing: " << outfile << std::endl;
		if (!factory.write(outfile, image))
		{
			std::cout << "error writing file!" << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;
}
