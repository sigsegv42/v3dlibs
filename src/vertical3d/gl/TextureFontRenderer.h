/**
 * (c) Joshua Farr <j.wgasa@gmail.com>
 *
 */

#pragma once

#include "../font/TextureTextBuffer.h"
#include "VertexBuffer.h"
#include "Program.h"
#include "GLTexture.h"

namespace v3D
{

	/**
	 * A OpenGL Font renderer.
	 */
	class TextureFontRenderer
	{
		public:
			TextureFontRenderer();
			TextureFontRenderer(boost::shared_ptr<TextureTextBuffer> buffer, boost::shared_ptr<Program> program);
			virtual ~TextureFontRenderer();

			boost::shared_ptr<TextureTextBuffer> buffer();

			void upload();
			void render();

		private:
			boost::shared_ptr<TextureTextBuffer> buffer_;
			boost::shared_ptr<Program> program_;
			VertexBuffer vertexBuffer_;
			GLTexture texture_;
	};

}; // end namespace v3D

