/**
 * (c) Joshua Farr <j.wgasa@gmail.com>
 *
 */

#include "TextureTextBuffer.h"
#include "../image/TextureAtlas.h"
#include "TextureFont.h"

#include <glm/gtc/matrix_transform.hpp>
#include <log4cxx/logger.h>

using namespace v3D;

TextureTextBuffer::TextureTextBuffer() :
	ascender_(0.0f),
	descender_(0.0f),
	lineStart_(0)
{
}

void TextureTextBuffer::addCharacter(glm::vec2 & pen, const Markup & markup, wchar_t current, wchar_t previous)
{
	if (current == L'\n')
	{
		pen.x = origin_.x;
		pen.y += markup.font_->height() - markup.font_->descender();
		/*
		descender_ = 0.0f;
		ascender_ = 0.0f;
		*/
		lineStart_ = items_.size();
		// newlines don't actually generate any vertex data
		return;
	}
	boost::shared_ptr<TextureFont::Glyph> glyph = markup.font_->glyph(current);
	boost::shared_ptr<TextureFont::Glyph> black = markup.font_->glyph(-1);
	if (!glyph)
	{
		return;
	}
	unsigned int vcount = 0;
	unsigned int icount = 0;
	unsigned int istart = indices_.size();
	unsigned int vstart = xyz_.size();

	if (markup.backgroundColor_.a > 0.0f)
	{
        glm::vec2 xy0(pen.x, pen.y + markup.font_->descender());
		glm::vec2 xy1(pen.x + glyph->advance_.x, xy0.y + markup.font_->height() + markup.font_->linegap());

		addQuad(xy0, xy1, black->st_[0], black->st_[1], markup.backgroundColor_, markup.gamma_);

		vcount += 4;
		icount += 6;
	}

	if (markup.underline_)
	{
        glm::vec2 xy0(pen.x, pen.y + markup.font_->underlinePosition());
		glm::vec2 xy1(pen.x + glyph->advance_.x, xy0.y + markup.font_->underlineThickness());

		addQuad(xy0, xy1, black->st_[0], black->st_[1], markup.underlineColor_, markup.gamma_);

		vcount += 4;
		icount += 6;
	}

	if (markup.overline_)
	{
		glm::vec2 xy0(pen.x, pen.y + markup.font_->ascender());
		glm::vec2 xy1(pen.x + glyph->advance_.x, xy0.y + markup.font_->underlineThickness());

		addQuad(xy0, xy1, black->st_[0], black->st_[1], markup.overlineColor_, markup.gamma_);

		vcount += 4;
		icount += 6;
	}

	if (markup.strikethrough_)
	{
		glm::vec2 xy0(pen.x, pen.y + markup.font_->ascender() *.33f);
		glm::vec2 xy1(pen.x + glyph->advance_.x, xy0.y + markup.font_->underlineThickness());

		addQuad(xy0, xy1, black->st_[0], black->st_[1], markup.overlineColor_, markup.gamma_);

		vcount += 4;
		icount += 6;
	}

	// actual glyph
	glm::vec2 xy0(pen.x + glyph->offset_.x, (int)(pen.y + glyph->height_ - glyph->offset_.y));
	glm::vec2 xy1(xy0.x + glyph->width_, (int)(xy0.y - glyph->offset_.y));

	addQuad(xy0, xy1, glyph->st_[0], glyph->st_[1], markup.foregroundColor_, markup.gamma_);

	vcount += 4;
	icount += 6;

	pen.x += glyph->advance_.x;
	items_.push_back(glm::ivec4(vstart, vcount, istart, icount));
}

void TextureTextBuffer::addQuad(const glm::vec2 & xy0, const glm::vec2 & xy1, const glm::vec2 & uv0, const glm::vec2 & uv1, const glm::vec4 & color, float gamma)
{
	unsigned int vcount = xyz_.size();

	// uv[0,1].t are flipped so y(0) can be top of screen (otherwise texture is upside down)
	addVertex(glm::vec3(xy0.x, xy0.y, 0.0f), glm::vec2(uv0.s, uv1.t), color, xy0.x - ((int)xy0.x), gamma);
	addVertex(glm::vec3(xy0.x, xy1.y, 0.0f), glm::vec2(uv0.s, uv0.t), color, xy0.x - ((int)xy0.x), gamma);
	addVertex(glm::vec3(xy1.x, xy1.y, 0.0f), glm::vec2(uv1.s, uv0.t), color, xy1.x - ((int)xy1.x), gamma);
	addVertex(glm::vec3(xy1.x, xy0.y, 0.0f), glm::vec2(uv1.s, uv1.t), color, xy1.x - ((int)xy1.x), gamma);

	// Use CCW winding so that the ortho matrix can put y(0) at the top of the screen
	// CW winding tri indices would be (0, 1, 2), (0, 2, 3)
	indices_.push_back(vcount);
	indices_.push_back(vcount+2);
	indices_.push_back(vcount+1);
	indices_.push_back(vcount);
	indices_.push_back(vcount+3);
	indices_.push_back(vcount+2);
}

void TextureTextBuffer::addVertex(glm::vec3 position, glm::vec2 texture, glm::vec4 color, float shift, float gamma)
{
	xyz_.push_back(position);
	uv_.push_back(texture);
	rgba_.push_back(color);
	shift_.push_back(shift);
	gamma_.push_back(gamma);
}

void TextureTextBuffer::addText(glm::vec2 & pen, const Markup & markup, const std::wstring & text)
{
	if (xyz_.size() == 0)
	{
		origin_ = pen;
	}
	/*
	if (markup.font_->ascender() > ascender_)
	{
		float dy = markup.font_->ascender() - ascender_;
		for (unsigned int i = lineStart_; i < items_.size(); ++i)
		{
			for (int j = items_[i][0]; j < items_[i][0] + items_[i][1]; ++j)
			{
				xyz_[j].y -= dy;
			}
		}
		ascender_ = markup.font_->ascender();
		pen.y -= dy;
	}
	if (markup.font_->descender() < descender_)
	{
		descender_ = markup.font_->descender();
	}
	*/
	addCharacter(pen, markup, text[0], 0);
	for (unsigned int i = 1; i < text.length(); ++i)
	{
		addCharacter(pen, markup, text[i], text[i - 1]);
	}
}

void TextureTextBuffer::clear()
{
	// reset all of the underlying vertex buffer data sources
	xyz_.clear();
	rgba_.clear();
	uv_.clear();
	shift_.clear();
	gamma_.clear();
	items_.clear();
	indices_.clear();
}


std::vector<glm::vec3> & TextureTextBuffer::xyz()
{
	return xyz_;
}

std::vector<glm::vec4> & TextureTextBuffer::rgba()
{
	return rgba_;
}

std::vector<glm::vec2> & TextureTextBuffer::uv()
{
	return uv_;
}

std::vector<float> & TextureTextBuffer::shift()
{
	return shift_;
}

std::vector<float> & TextureTextBuffer::gamma()
{
	return gamma_;
}

std::vector<unsigned int> & TextureTextBuffer::indices()
{
	return indices_;
}
