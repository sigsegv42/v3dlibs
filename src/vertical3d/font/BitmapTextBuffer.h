/**
 * (c) Joshua Farr <j.wgasa@gmail.com>
 */

#pragma once

#include <glm/glm.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

namespace v3D
{

	class BitmapFont;

	class BitmapTextBuffer
	{
		public:
			/**
			 * Construct a new text buffer
			 *
			 * @param font the bitmap font to be rendered with this buffer
			 * @param program the text GL shader program used for bitmap font rendering
			 */
			BitmapTextBuffer(boost::shared_ptr<BitmapFont> font);

			/**
			 * Allocate the text buffer with a string of text
			 *
			 * @param vec2 pen window position to draw text
			 * @param string txt string of text
			 * @param vec4 color the text color
			 */
			void text(glm::vec2 & pen, const std::string & txt, const glm::vec4 & color);

			/**
			 * Clear the existing text buffer
			 */
			void clear();
			void invalidate();
			bool dirty() const;

			/**
			 * Calculate the width of a string of text
			 *
			 * @param string txt string of text
			 * 
			 * @return size_t pixel width of the string when rendered
			 */
			size_t width(const std::string & txt);

			std::vector<glm::vec3> & vertices();
			std::vector<glm::vec2> & uvs();
			std::vector<glm::vec4> & colors();
			std::vector<unsigned int> & indices();

		private:
			boost::shared_ptr<BitmapFont> font_;
			bool dirty_;

			std::vector<glm::vec3> vertices_;
			std::vector<glm::vec2> uvs_;
			std::vector<glm::vec4> colors_;
			std::vector<unsigned int> indices_;
	};

}