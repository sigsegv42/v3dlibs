/**
 * (c) Joshua Farr <j.wgasa@gmail.com>
 */

#include "BitmapTextBuffer.h"
#include "BitmapFont.h"

#include <vector>

using namespace v3D;

BitmapTextBuffer::BitmapTextBuffer(boost::shared_ptr<BitmapFont> font) : 
	font_(font), 
	dirty_(true)
{
}

size_t BitmapTextBuffer::width(const std::string & txt)
{
	size_t w = 0;
	for (unsigned int index = 0; index < txt.length(); ++index)
	{
		BitmapFont::CharDescriptor character = font_->character(txt[index]);
		w += character.xAdvance_;
	}
	return w;
}

void BitmapTextBuffer::text(glm::vec2 & pen, const std::string & txt, const glm::vec4 & color)
{
	float charsetWidth = font_->charsetWidth();
	float charsetHeight = font_->charsetHeight();

	vertices_.resize(txt.length() * 6);
	uvs_.resize(txt.length() * 6);
	colors_.resize(txt.length() * 6);
	indices_.resize(txt.length() * 6);
	unsigned int vcount = 0;

	for (unsigned int index = 0; index < txt.length(); ++index)
	{
		BitmapFont::CharDescriptor character = font_->character(txt[index]);
		float charX = character.x_;
		float charY = character.y_;
		float width = character.width_;
		float height = character.height_;
		float offsetX = character.xOffset_;
		float offsetY = character.yOffset_;

		// upper left
		uvs_[vcount].s = charX / charsetWidth;
		uvs_[vcount].t = charY / charsetHeight;
		vertices_[vcount].x = pen.x + offsetX;
		vertices_[vcount].y = pen.y + offsetY;
		vertices_[vcount].z = 0.0f;
		colors_[vcount] = color;

		// upper right
		uvs_[vcount + 1].s = (charX + width) / charsetWidth;
		uvs_[vcount + 1].t = charY / charsetHeight;
		vertices_[vcount + 1].x = width + pen.x + offsetX;
		vertices_[vcount + 1].y = pen.y + offsetY;
		vertices_[vcount + 1].z = 0.0f;
		colors_[vcount + 1] = color;

		// lower right
		uvs_[vcount + 2].s = (charX + width) / charsetWidth;
		uvs_[vcount + 2].t = (charY + height) / charsetHeight;
		vertices_[vcount + 2].x = width + pen.x + offsetX;
		vertices_[vcount + 2].y = height + pen.y + offsetY;
		vertices_[vcount + 2].z = 0.0f;
		colors_[vcount + 2] = color;

		// lower left
		uvs_[vcount + 3].s = charX / charsetWidth;
		uvs_[vcount + 3].t = (charY + height) / charsetHeight;
		vertices_[vcount + 3].x = pen.x + offsetX;
		vertices_[vcount + 3].y = height + pen.y + offsetY;
		vertices_[vcount + 3].z = 0.0f;
		colors_[vcount + 3] = color;

		indices_.push_back(vcount);
		indices_.push_back(vcount + 1);
		indices_.push_back(vcount + 3);

		indices_.push_back(vcount + 3);
		indices_.push_back(vcount + 1);
		indices_.push_back(vcount + 2);

		vcount += 4;
		pen.x += character.xAdvance_;
	}
	/*
	buffer_.attribute(0, 3, v3D::VertexBuffer::ATTRIBUTE_TYPE_VERTEX, vertices.size());
	buffer_.attribute(1, 2, v3D::VertexBuffer::ATTRIBUTE_TYPE_NORMAL, uvs.size());
	buffer_.attribute(2, 4, v3D::VertexBuffer::ATTRIBUTE_TYPE_COLOR, colors.size());

	buffer_.allocate();

	buffer_.data3f(0, vertices);
	buffer_.data2f(1, uvs);
	buffer_.data4f(2, colors);

	buffer_.indices(indices);
	*/
	dirty_ = false;
}

void BitmapTextBuffer::clear()
{
	// allocating effectively clears the buffer
	//buffer_.allocate();
	indices_.clear();
	vertices_.clear();
	uvs_.clear();
	colors_.clear();
}

void BitmapTextBuffer::invalidate()
{
	dirty_ = true;
}

bool BitmapTextBuffer::dirty() const
{
	return dirty_;
}

std::vector<glm::vec3> & BitmapTextBuffer::vertices()
{
	return vertices_;
}

std::vector<glm::vec2> & BitmapTextBuffer::uvs()
{
	return uvs_;
}

std::vector<glm::vec4> & BitmapTextBuffer::colors()
{
	return colors_;
}

std::vector<unsigned int> & BitmapTextBuffer::indices()
{
	return indices_;
}
