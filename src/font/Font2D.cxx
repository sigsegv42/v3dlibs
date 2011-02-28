#include "Font2D.h"

#include "../3dtypes/3dtypes.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <windows.h>
#include <gl/gl.h>

#include <string>
#include <cmath>
#include <algorithm>

#undef max

using namespace v3D;

Font2D::Font2D() : _typeface("Courier New"), _size(24), _line_height(0), _tex_line_height(0.0f)
{
}

Font2D::Font2D(const std::string & face, unsigned int size) : _typeface(face), _size(size), _line_height(0), _tex_line_height(0.0f)
{
}

Font2D::~Font2D()
{
}

unsigned int Font2D::style(void) const
{
	return _style;
}

void Font2D::style(unsigned int attribs)
{
	_style = attribs;
}

int Font2D::size(void) const
{
	return _size;
}

void Font2D::size(int s)
{
	_size = s;
}

std::string Font2D::typeface(void) const
{
	return _typeface;
}

void Font2D::typeface(const std::string & face)
{
	_typeface = face;
}

boost::shared_ptr<Texture> Font2D::texture(void) const
{
	return _texture;
}

// NOTE: fonts aren't locale or language aware - there is a limited predefined character range supported. 
// freetype font loading based on gpwiki sample code
bool Font2D::build(void)
{
	// the set of all characters to be loaded from the font file
	const std::string charset("abcdefghijklmnopqrstuvwxyz"
							  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
							  "1234567890~!@#$%^&*()-=+;:"
							  " _'\",./?[]|\\<>{}`\xFF");

	// initialize freetype library
	FT_Library library;
	FT_Error error;
	if ((error = FT_Init_FreeType(&library)) != 0)
	{
		return false;
	}
	// load font file
	FT_Face face;
	std::string filename(_typeface);
	if ((error = FT_New_Face(library, filename.c_str(), 0, &face)) != 0)
	{
		return false;
	}
	// make sure this is a scalable truetype font
	if (!(face->face_flags & FT_FACE_FLAG_SCALABLE) || !(face->face_flags & FT_FACE_FLAG_HORIZONTAL))
	{
		return false;
	}

	// set the font size
	if ((error = FT_Set_Pixel_Sizes(face, _size, 0)) != 0)
	{
		return false;
	}

	// horizontal character padding
	const unsigned int pad = 3;
	// texture dimensions - width is fixed
	unsigned int image_width = 256;
	// image height is determined by the number of rows of character images are required
	unsigned int image_height = 0;
	// we need to figure out the maximum descent & ascent of all the glyphs in the charset
	int max_descent = 0;
	int max_ascent = 0;
	// the number of rows of glyphs that will be in the texture
	unsigned int rows = 1;
	// the space used on the current row by glyphs so far
	unsigned int row_space = image_width - pad;

	// iterate over each character we want to use in the font
	for (size_t i = 0; i < charset.size(); i++)
	{
		unsigned int charcode = charset[i];
		if (charset[i] == '\xFF')
			charcode = 0;

		// load the glyph and render the bitmap
		if ((error = FT_Load_Char(face, charcode, FT_LOAD_RENDER)) != 0)
		{
			return false;
		}
		// get the advance in pixels and added padding
		// glyph metrics are stored in 26.6 pixel format (1/64 pixels)
		unsigned int advance = (face->glyph->metrics.horiAdvance >> 6) + pad;

		// not enough room on this row for this glyph
		if (advance > row_space) 
		{
			// reset counter and increment row count
			row_space = image_width - pad;
			rows++;
		}
		// take up space for this glyph in the row
		row_space -= advance;

		max_ascent = std::max(face->glyph->bitmap_top, max_ascent);
		max_descent = std::max(face->glyph->bitmap.rows - face->glyph->bitmap_top, max_descent);
	}

	// calculate final texture size
	unsigned int requested_height = (max_ascent + max_descent + pad) * rows + pad;
	// the size must be a power of two
	image_height = npot(requested_height);

	boost::shared_ptr<Image> image(new Image(image_width, image_height, 8));

	unsigned int x = pad;
	unsigned int y = pad + max_ascent;

	for (size_t i = 0; i < charset.size(); i++)
	{
		unsigned char charcode = charset[i];
		if (charset[i] == '\xFF')
			charcode = 0;

		// load the glyph and render the bitmap
		if ((error = FT_Load_Char(face, charcode, FT_LOAD_RENDER)) != 0)
		{
			return false;
		}
		unsigned int advance = (face->glyph->metrics.horiAdvance >> 6) + pad;
		if (advance > image_width - x)
		{
			x = pad;
			y += (max_ascent + max_descent + pad);
		}
		// create glyph
		Glyph glyph;
		glyph._x1 = static_cast<float>(x) / image_width;
		glyph._x2 = static_cast<float>(x + (advance - pad)) / image_width;
		glyph._y1 = static_cast<float>((y - max_ascent)) / image_height;
		glyph._advance = (advance - pad);

		_glyphs[charcode] = glyph;

		// copy bitmap to texture image
		for (int row = 0; row < face->glyph->bitmap.rows; row++)
		{
			for (int pixel = 0; pixel < face->glyph->bitmap.width; pixel++)
			{
				(*image)[(x + face->glyph->bitmap_left + pixel) + (y - face->glyph->bitmap_top + row) * image_width] =
					face->glyph->bitmap.buffer[pixel + row * face->glyph->bitmap.pitch];
			}
		}
		x += advance;
	}

	FT_Done_FreeType(library);

	_texture = boost::shared_ptr<Texture>(new Texture(image));

	_line_height = max_ascent + max_descent;
	_tex_line_height = static_cast<float>(_line_height) / image_height;

	return true;
}

unsigned int Font2D::width(const std::string & str) const
{
	unsigned int w = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		unsigned char ch = str[i];
		w += width(ch);
	}
	return w;
}

unsigned int Font2D::height(void) const
{
	return _line_height;
}

unsigned int Font2D::width(unsigned char charcode) const
{
	std::map<unsigned char, Glyph>::const_iterator iter = _glyphs.find(charcode);
	if (iter != _glyphs.end())
		return iter->second._advance;
	return 0;
}


void Font2D::print(const std::string & text, float x, float y)
{
	// set texture & blending states for font drawing
	glPushAttrib(GL_TEXTURE_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	if (!_texture->bind())
		return;

	glBegin(GL_QUADS);
	for (size_t i = 0; i < text.size(); i++)
	{
		std::map<unsigned char, Glyph>::iterator iter = _glyphs.find(text[i]);
		if (iter == _glyphs.end())
			iter = _glyphs.begin();
		Glyph * glyph = &(iter->second);

		glTexCoord2f(glyph->_x1, glyph->_y1);
		glVertex2f(x, y);

		glTexCoord2f(glyph->_x1, glyph->_y1 + _tex_line_height);
		glVertex2f(x, y + _line_height);

		glTexCoord2f(glyph->_x2, glyph->_y1 + _tex_line_height);
		glVertex2f(x + glyph->_advance, y + _line_height);

		glTexCoord2f(glyph->_x2, glyph->_y1);
		glVertex2f(x + glyph->_advance, y);

		x += glyph->_advance;
	}
	glEnd();

	// reset texture & blend states to their initial settings
	glPopAttrib();
}
