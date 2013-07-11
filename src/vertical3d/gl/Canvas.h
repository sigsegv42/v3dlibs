/**
 * (c) Joshua Farr <j.wgasa@gmail.com>
 *
 */

#include "VertexBuffer.h"

#include <glm/glm.hpp>
#include <deque>

namespace v3D
{

	class Program;

	class Canvas
	{
		public:
			Canvas(boost::shared_ptr<Program> program);
			Canvas(boost::shared_ptr<Program> program, unsigned int width, unsigned int height);
			~Canvas();

			void upload();
			void render();
			void clear();
			void resize(unsigned int width, unsigned int height);

			void rect(unsigned int left, unsigned int right, unsigned int top, unsigned int bottom, glm::vec3 color);
			void circle(size_t sides, size_t size, glm::vec3 color);
			void push();
			void pop();
			void translate(glm::vec2 pos);

		protected:
			void addVertex(glm::vec3 position, glm::vec4 color);
			void addQuad(const glm::vec2 & xy0, const glm::vec2 & xy1, const glm::vec4 & color);

		private:
			unsigned int width_;
			unsigned int height_;
			std::deque<glm::mat4> modelView_;
			glm::mat4 projection_;
			VertexBuffer buffer_;
			boost::shared_ptr<Program> program_;
			unsigned int vao_;

			// vertex data
			std::vector<glm::vec3> xyz_;
			std::vector<glm::vec4> rgba_;
			std::vector<unsigned int> indices_;
	};

};