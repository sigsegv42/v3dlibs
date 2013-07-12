/**
 * (c) Joshua Farr <j.wgasa@gmail.com>
 *
 */

#include "Canvas.h"
#include "Program.h"
#include "../3dtypes/3dtypes.h"

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

using namespace v3D;

Canvas::Canvas(boost::shared_ptr<Program> program) :
	buffer_(VertexBuffer::BUFFER_TYPE_DYNAMIC),
	vao_(0),
	program_(program)
{
	push();
}

Canvas::Canvas(boost::shared_ptr<Program> program, unsigned int width, unsigned int height) :
	width_(width),
	height_(height),
	buffer_(VertexBuffer::BUFFER_TYPE_DYNAMIC),
	program_(program),
	vao_(0)
{
	push();
}

Canvas::~Canvas()
{
}

void Canvas::clear() 
{
	xyz_.clear();
	indices_.clear();
	rgba_.clear();
}

void Canvas::addQuad(const glm::vec2 & xy0, const glm::vec2 & xy1, const glm::vec4 & color)
{
	unsigned int vcount = xyz_.size();

	addVertex(glm::vec3(xy0.x, xy0.y, 0.0f), color);
	addVertex(glm::vec3(xy0.x, xy1.y, 0.0f), color);
	addVertex(glm::vec3(xy1.x, xy1.y, 0.0f), color);
	addVertex(glm::vec3(xy1.x, xy0.y, 0.0f), color);

	// Use CCW winding so that the ortho matrix can put y(0) at the top of the screen
	// CW winding tri indices would be (0, 1, 2), (0, 2, 3)
	indices_.push_back(vcount);
	indices_.push_back(vcount+2);
	indices_.push_back(vcount+1);
	indices_.push_back(vcount);
	indices_.push_back(vcount+3);
	indices_.push_back(vcount+2);
}

void Canvas::addVertex(glm::vec3 position, glm::vec4 color)
{
	xyz_.push_back(position);
	rgba_.push_back(color);
}

void Canvas::upload()
{
	if (vao_ == 0)
	{
		glGenVertexArrays(1, &vao_);
	}
	glBindVertexArray(vao_);

	buffer_.attribute(0, 3, v3D::VertexBuffer::ATTRIBUTE_TYPE_VERTEX, xyz_.size());
	buffer_.attribute(1, 4, v3D::VertexBuffer::ATTRIBUTE_TYPE_COLOR, rgba_.size());

	buffer_.allocate();

	buffer_.data3f(0, xyz_);
	buffer_.data4f(1, rgba_);

	buffer_.indices(indices_);
}

void Canvas::render()
{
	program_->enable();
	buffer_.render();
	program_->disable();
}

void Canvas::resize(unsigned int width, unsigned int height)
{
	width_ = width;
	height_ = height;
	glViewport(0, 0, width, height);
	float w = static_cast<float>(width);
	float h = static_cast<float>(height);
	projection_ = glm::ortho(0.0f, w, h, 0.0f, -1.0f, 1.0f);
	program_->enable();
	unsigned int projectionMatrix = program_->uniform("projectionMatrix");
	glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(projection_));
	program_->disable();
}

void Canvas::rect(unsigned int left, unsigned int right, unsigned int top, unsigned int bottom, glm::vec3 color)
{
	glm::mat4 mv = modelView_.back();
	glm::vec4 p(left, bottom, 0.0f, 1.0f);
	p = mv * p;
	glm::vec2 xy0(p.x, p.y);
	p = glm::vec4(right, top, 0.0f, 1.0f);
	p = mv * p;
	glm::vec2 xy1(p.x, p.y);
	glm::vec4 rgba(color, 0.0f);
	addQuad(xy0, xy1, rgba);
}

void Canvas::push()
{
	glm::mat4 identity(1.0f);
	modelView_.push_back(identity);
}

void Canvas::pop()
{
	if (modelView_.size() != 1)
	{
		modelView_.pop_back();
	}
}

void Canvas::translate(glm::vec2 pos)
{
	glm::mat4 & mv = modelView_.back();
	glm::vec3 p(pos, 0.0f);
	mv = glm::translate(mv, p);
}

void Canvas::circle(size_t sides, size_t size, glm::vec3 color)
{
	unsigned int vcount = xyz_.size();
	glm::mat4 mv = modelView_.back();
	glm::vec4 middle(0.0f, 0.0f, 0.0f, 1.0f);
	middle = mv * middle;
	glm::vec4 rgba(color, 0.0f);
	glm::vec3 p0(middle.x, middle.y, middle.z);
	addVertex(p0, rgba);
	float delta = 2.0f * PI / sides;
	unsigned int index = 1;
	for (size_t k = 0; k < sides; k++)
	{
		glm::vec4 p1(0.0f, 0.0f, 0.0f, 1.0f);
		p1[0] = cos(delta * k) * size;
		p1[1] = sin(delta * k) * size;
		size_t n = k + 1;
		if (n == sides)
		{
			n = 0;
		}
		glm::vec4 p2(0.0f, 0.0f, 0.0f, 1.0f);
		p2[0] = cos(delta * n) * size;
		p2[1] = sin(delta * n) * size;
		p1 = mv * p1;
		p2 = mv * p2;

		addVertex(glm::vec3(p2.x, p2.y, 0.0f), rgba);
		addVertex(glm::vec3(p1.x, p1.y, 0.0f), rgba);

		indices_.push_back(vcount);
		indices_.push_back(vcount + index);
		indices_.push_back(vcount + index + 1);
		index += 2;
	}
}
