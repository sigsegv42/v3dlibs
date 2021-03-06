/**
 * (c) Joshua Farr <j.wgasa@gmail.com>
 *
 */

#include "GLFontRenderer.h"

#include <GL/glew.h>

#include <cassert>
#include <iostream>

using namespace v3D;

GLFontRenderer::GLFontRenderer()
{

}

GLFontRenderer::GLFontRenderer(const Font2D &f) : font_(f)
{ 
	texture_.create(font_.texture()->image());
}

GLFontRenderer::~GLFontRenderer()
{
}

void GLFontRenderer::print(const std::string & text, float x, float y)
{
	// set texture & blending states for font drawing
	glPushAttrib(GL_TEXTURE_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	if (!texture_.bind())
	{
		return;
	}

	glBegin(GL_QUADS);
	for (size_t i = 0; i < text.size(); i++)
	{
		const Font2D::Glyph * glyph = font_.glyph(text[i]);

		glTexCoord2f(glyph->x1_, glyph->y1_);
		glVertex2f(x, y);

		glTexCoord2f(glyph->x1_, glyph->y1_ + font_.textureHeight());
		glVertex2f(x, y + font_.height());

		glTexCoord2f(glyph->x2_, glyph->y1_ + font_.textureHeight());
		glVertex2f(x + glyph->advance_, y + font_.height());

		glTexCoord2f(glyph->x2_, glyph->y1_);
		glVertex2f(x + glyph->advance_, y);

		x += glyph->advance_;
	}
	glEnd();

	// reset texture & blend states to their initial settings
	glPopAttrib();
}
