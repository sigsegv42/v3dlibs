/**
 * (c) Joshua Farr <j.wgasa@gmail.com>
 *
 */
#include "GLTexture.h"

#include <GL/glew.h>

#include <cassert>
#include <iostream>

#include <log4cxx/logger.h>

using namespace v3D;

GLTexture::GLTexture()
{ 
}

GLTexture::GLTexture(boost::shared_ptr<Image> image)
{
	create(image);
}

GLTexture::GLTexture(const Texture &t) : Texture(t)
{ 
}

GLTexture::~GLTexture()
{
	if (!isnull())
	{
		unsigned int tex_id = id();
		glDeleteTextures(1, &tex_id);
	}
}


void GLTexture::wrap(bool repeat)
{ 
	Texture::wrap(repeat);
	if (!bind())
	{
		return;
	}
	if (!repeat)
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

bool GLTexture::bind()
{
	unsigned int tex_id = id();
	if (tex_id != -1)
	{
		glBindTexture(GL_TEXTURE_2D, tex_id);
	}
	else
	{
		log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("v3d.gl"));
		LOG4CXX_DEBUG(logger, "GLTexture::bind - bad texture id!");
		return false;
	}

	return true;
}

bool GLTexture::create(boost::shared_ptr<Image> image)
{
	Texture::create(image);
	unsigned int tex_id = id();
	// Build A Texture From The Data
	glGenTextures(1, &tex_id);				// Generate OpenGL texture IDs
	id(tex_id);

	glBindTexture(GL_TEXTURE_2D, tex_id);	// Bind Our Texture

	int format = GL_RGB;
	int internalformat = GL_RGB;
	if (image->bpp() == 24) // is the image 24 bits?
	{
		format = GL_RGB;
		internalformat = GL_RGB;
	}
	else if (image->bpp() == 8)
	{
		format = GL_ALPHA;
		internalformat = GL_ALPHA8;
	}

	// test to make sure texture will fit first
	glTexImage2D(GL_PROXY_TEXTURE_2D, 0, internalformat, image->width(), image->height(), 0, format, GL_UNSIGNED_BYTE, image->data());
	GLint params[1];
	glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, params);
	if (params[0] == 0)
	{
		return false;
	}
	// load the image data into texture memory
	glTexImage2D(GL_TEXTURE_2D, 0, internalformat, image->width(), image->height(), 0, format, GL_UNSIGNED_BYTE, image->data());

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);		// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		// Linear Filtered

	if (!Texture::wrap())
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	return true;
}
