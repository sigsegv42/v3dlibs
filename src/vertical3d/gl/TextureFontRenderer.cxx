/**
 * (c) Joshua Farr <j.wgasa@gmail.com>
 *
 */

#include "TextureFontRenderer.h"
#include "../image/TextureAtlas.h"
#include "../font/TextureFontCache.h"

#include <GL/glew.h>

using namespace v3D;

TextureFontRenderer::TextureFontRenderer() :
	vertexBuffer_(v3D::VertexBuffer::BUFFER_TYPE_DYNAMIC)
{

}

TextureFontRenderer::TextureFontRenderer(boost::shared_ptr<TextureTextBuffer> buffer, boost::shared_ptr<Program> program) :
	program_(program),
	buffer_(buffer),
	vertexBuffer_(v3D::VertexBuffer::BUFFER_TYPE_DYNAMIC)
{
}

TextureFontRenderer::~TextureFontRenderer()
{
}

boost::shared_ptr<TextureTextBuffer> TextureFontRenderer::buffer()
{
	return buffer_;
}

void TextureFontRenderer::upload()
{
	vertexBuffer_.attribute(0, 3, v3D::VertexBuffer::ATTRIBUTE_TYPE_VERTEX, buffer_->xyz().size());
	vertexBuffer_.attribute(1, 2, v3D::VertexBuffer::ATTRIBUTE_TYPE_NORMAL, buffer_->uv().size());
	vertexBuffer_.attribute(2, 4, v3D::VertexBuffer::ATTRIBUTE_TYPE_COLOR, buffer_->rgba().size());
	vertexBuffer_.attribute(3, 1, v3D::VertexBuffer::ATTRIBUTE_TYPE_GENERIC, buffer_->shift().size());
	vertexBuffer_.attribute(4, 1, v3D::VertexBuffer::ATTRIBUTE_TYPE_GENERIC, buffer_->gamma().size());

	vertexBuffer_.allocate();

	vertexBuffer_.data3f(0, buffer_->xyz());
	vertexBuffer_.data2f(1, buffer_->uv());
	vertexBuffer_.data4f(2, buffer_->rgba());
	vertexBuffer_.data1f(3, buffer_->shift());
	vertexBuffer_.data1f(4, buffer_->gamma());

	vertexBuffer_.indices(buffer_->indices());

	texture_.create(buffer_->cache()->atlas()->image());
}

void TextureFontRenderer::render()
{
	boost::shared_ptr<TextureAtlas> atlas = buffer_->cache()->atlas();
	glEnable(GL_BLEND);
	if (atlas->depth() == 1)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		vertexBuffer_.render();
	}
	else
	{
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glBlendColor(1.0f, 1.0f, 1.0f, 1.0f);
		program_->enable();
		unsigned int texture = program_->uniform("texture");
		glUniform1i(texture, 0);
		unsigned int pixel = program_->uniform("pixel");
		float width = 1.0f / static_cast<float>(atlas->width());
		float height = 1.0f / static_cast<float>(atlas->height());
		float depth = static_cast<float>(atlas->depth());
		glUniform3f(pixel, width, height, depth);
		vertexBuffer_.render();
		program_->disable();
	}
}
