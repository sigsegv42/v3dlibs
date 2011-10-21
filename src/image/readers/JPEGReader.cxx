#include "JPEGReader.h"

#ifdef  __cplusplus
	extern "C" {
		#include <jpeglib.h>
	}
#endif

#include <fstream>
#include <iostream>

using namespace v3D;

JPEGReader::JPEGReader()
{
}

JPEGReader::~JPEGReader()
{
}

boost::shared_ptr<Image> JPEGReader::read(const std::string &filename)
{
	boost::shared_ptr<Image> empty_ptr;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	// Initialize the JPEG decompression object with default error handling.
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	// open the file
	FILE * fp;
	if ((fp = fopen(filename.c_str(), "rb")) != 0)
	{
		return empty_ptr;
	}

	// Specify data source for decompression
	jpeg_stdio_src(&cinfo, fp);

	// Read file header, set default decompression parameters
	jpeg_read_header(&cinfo, TRUE);

	jpeg_calc_output_dimensions(&cinfo);

	// Create decompressor output buffer.
	JDIMENSION row_width = cinfo.output_width * cinfo.output_components;
	JSAMPARRAY buffer;
	JDIMENSION buffer_height;
	buffer = (*cinfo.mem->alloc_sarray)
    ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_width, (JDIMENSION) 1);
	buffer_height = 1;

	// Adjust default decompression parameters by re-parsing the options
	(void) jpeg_start_decompress(&cinfo);

	boost::shared_ptr<Image> img(new Image(cinfo.image_width, cinfo.image_height, 24));
	unsigned char * data = img->data();

	// Process data
	JDIMENSION num_scanlines = 0;
	int row = cinfo.output_height - 1;
	unsigned int index = 0;
	while (cinfo.output_scanline < cinfo.output_height) 
	{
		num_scanlines = jpeg_read_scanlines(&cinfo, buffer, buffer_height);

		index = row * cinfo.output_components * cinfo.output_width;
		for (unsigned int i = 0; i < cinfo.output_width; i++)
		{
			data[index] = buffer[0][(i * cinfo.output_components)];
			data[index + 1] = buffer[0][(i * cinfo.output_components) + 1];
			data[index + 2] = buffer[0][(i * cinfo.output_components) + 2];
			index += 3;
		}
		row--;
	}

	// Finish decompression and release memory.
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	fclose(fp);
	return img;
}
