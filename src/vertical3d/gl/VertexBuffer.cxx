/**
 * (c) Joshua Farr <j.wgasa@gmail.com>
 *
 */

#include "VertexBuffer.h"

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include <log4cxx/logger.h>

using namespace v3D;

VertexBuffer::VertexBuffer(BufferType type) :
	ebo_(0),
	vbo_(0),
	type_(type),
	allocated_(false)
{
}

VertexBuffer::~VertexBuffer()
{
	if (ebo_ != 0)
	{
		glDeleteBuffers(1, &ebo_);
	}
	if (vbo_ != 0)
	{
		glDeleteBuffers(1, &vbo_);
	}
}

void VertexBuffer::attribute(unsigned int position, unsigned int size, AttributeType type, unsigned int length)
{
	VertexAttribute attr;
	attr.position_ = position;
	attr.size_ = size;
	attr.type_ = type;
	attr.length_ = length;
	attr.stride_ = sizeof(float) * size;

	size_t offset = 0;
	bool exists = false;
	unsigned int index;
	for (unsigned int i = 0; i < attributes_.size(); i++)
	{
		if (attributes_[i].position_ < position)
		{
			offset += attributes_[i].stride_ * attributes_[i].length_;
		}
		if (attributes_[i].position_ == position)
		{
			exists = true;
			index = i;
		}
	}
	attr.offset_ = offset;

	// if the attribute in the same poisition has previously been set then just replace the old version
	if (exists)
	{
		attributes_[index] = attr;
	}
	else
	{
		attributes_.push_back(attr);
	}
}

void VertexBuffer::indices(const std::vector<unsigned int> & data)
{
	indices_ = data.size();
	if (ebo_ == 0)
	{
		glGenBuffers(1, &ebo_);
	}
	GLenum usage;
	switch (type_)
	{
		case BUFFER_TYPE_STATIC:
			usage = GL_STATIC_DRAW;
			break;
		case BUFFER_TYPE_DYNAMIC:
			usage = GL_DYNAMIC_DRAW;
			break;
		default:
			usage = GL_STATIC_DRAW;
			break;
	}
	// NB - ebo's are bound to the vao so the vao must already be bound
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_ * sizeof(unsigned int), &data[0], usage);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexBuffer::indices(glm::ivec3 * data, size_t count)
{
	indices_ = count;
	if (ebo_ == 0)
	{
		glGenBuffers(1, &ebo_);
	}
	GLenum usage;
	switch (type_)
	{
		case BUFFER_TYPE_STATIC:
			usage = GL_STATIC_DRAW;
			break;
		case BUFFER_TYPE_DYNAMIC:
			usage = GL_DYNAMIC_DRAW;
			break;
		default:
			usage = GL_STATIC_DRAW;
			break;
	}
	// NB - ebo's are bound to the vao so the vao must already be bound
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_ * sizeof(unsigned int), &(data[0].x), usage);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void VertexBuffer::allocate()
{
	if (vbo_ == 0)
	{
		glGenBuffers(1, &vbo_);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	size_t bufferSize = 0;
	for (unsigned int i = 0; i < attributes_.size(); i++)
	{
		bufferSize += attributes_[i].stride_ * attributes_[i].length_;
	}

	GLenum usage;
	switch (type_)
	{
		case BUFFER_TYPE_STATIC:
			usage = GL_STATIC_DRAW;
			break;
		case BUFFER_TYPE_DYNAMIC:
			usage = GL_DYNAMIC_DRAW;
			break;
		default:
			usage = GL_STATIC_DRAW;
			break;
	}

	// allocate buffer
	glBufferData(GL_ARRAY_BUFFER, bufferSize, NULL, usage);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	allocated_ = true;
}

bool VertexBuffer::allocated() const
{
	return allocated_;
}

void VertexBuffer::data1f(unsigned int attr, const std::vector<float> & data)
{
	set(attr, &data[0], data.size());
}

void VertexBuffer::data2f(unsigned int attr, const std::vector<glm::vec2> & data)
{
	set(attr, glm::value_ptr(data[0]), data.size());
}

void VertexBuffer::data3f(unsigned int attr, const std::vector<glm::vec3> & data)
{
	set(attr, glm::value_ptr(data[0]), data.size());
}

void VertexBuffer::data4f(unsigned int attr, const std::vector<glm::vec4> & data)
{
	set(attr, glm::value_ptr(data[0]), data.size());
}

void VertexBuffer::set(unsigned int attr, const float * data, size_t size)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	unsigned int offset = attributes_[attr].offset_;
	size_t byteSize = attributes_[attr].stride_ * size;
	glBufferSubData(GL_ARRAY_BUFFER, offset, byteSize, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::render()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	for (unsigned int i = 0; i < attributes_.size(); i++)
	{
		glEnableVertexAttribArray(attributes_[i].position_);
		glVertexAttribPointer(
			attributes_[i].position_, 
			attributes_[i].size_, 
			GL_FLOAT, 
			GL_FALSE, 
			attributes_[i].stride_, 
			reinterpret_cast<void*>(attributes_[i].offset_)
		);
	}

	glDrawElements(GL_TRIANGLES, indices_, GL_UNSIGNED_INT, reinterpret_cast<void*>(0));

	for (unsigned int i = 0; i < attributes_.size(); i++)
	{
		glDisableVertexAttribArray(attributes_[i].position_);
	}
}
