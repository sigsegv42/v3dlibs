#include "Texture.h"
#include "ImageFactory.h"

#include <windows.h>
#include <gl/gl.h>

#include <cassert>
#include <iostream>

using namespace v3D;

Texture::Texture() : _type(UNKNOWN), _texID(-1), _wrap(false), _width(0), _height(0) 
{ 
}

Texture::Texture(const Texture &t) : _type(t._type), _texID(t._texID), _wrap(t._wrap), _width(0), _height(0)
{ 
}

Texture::Texture(boost::shared_ptr<Image> image) : _wrap(false)
{
	bool ok;
	ok = create(image);
	assert(ok);
}

Texture & Texture::operator = (const Texture & t)
{
	_type	= t._type;
	_texID	= t._texID;
	_wrap	= t._wrap;

	return *this;
}

bool Texture::operator == (const Texture & t) const 
{
	if (_texID == t._texID)
		return true;

	return false;
}

Texture::~Texture()
{
	if (!isnull())
		glDeleteTextures(1, &_texID);
}

unsigned int Texture::width(void) const
{
	return _width;
}

unsigned int Texture::height(void) const
{
	return _height;
}

bool Texture::isnull(void) 
{ 
	return (_type == UNKNOWN);
}

bool Texture::wrap(void) const 
{ 
	return _wrap; 
}

void Texture::wrap(bool repeat)
{ 
	_wrap = repeat; 
	if (!bind())
		return;
	if (!_wrap)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
}

bool Texture::bind(void)
{
	if (_texID != -1)
		glBindTexture(GL_TEXTURE_2D, _texID); 
	else
	{
		std::clog << "bad texid in bind!" << std::endl;
		return false;
	}

	return true;
}

bool Texture::create(boost::shared_ptr<Image> image)
{
	// Build A Texture From The Data
	glGenTextures(1, &_texID);				// Generate OpenGL texture IDs

	_type = LINEAR;
	glBindTexture(GL_TEXTURE_2D, _texID);	// Bind Our Texture

	int format = GL_RGB;
	_width = image->width();
	_height = image->height();
	int internalformat = 3;
	if (image->bpp() == 24) // is the image 24 bits?
	{
		format = GL_RGB;
		internalformat = 3;
	}
	else if (image->bpp() == 8)
	{
		format = GL_ALPHA;
		internalformat = GL_ALPHA8;
	}

	// test to make sure texture will fit first
	glTexImage2D(GL_PROXY_TEXTURE_2D, 0, internalformat, _width, _height, 0, format, GL_UNSIGNED_BYTE, image->data());
	GLint params[1];
	glGetTexLevelParameteriv (GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, params);
	if (params[0] == 0)
		return false;
	// load the image data into texture memory
	glTexImage2D(GL_TEXTURE_2D, 0, internalformat, _width, _height, 0, format, GL_UNSIGNED_BYTE, image->data());

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);		// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		// Linear Filtered

	if (!_wrap)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	return true;
}
