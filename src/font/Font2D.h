#ifndef INCLUDED_V3D_FONT2D
#define INCLUDED_V3D_FONT2D

#include "../image/Texture.h"

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>
#include <map>

namespace v3D
{

	/**
	 * 2D GL Font
	 */
	class Font2D
	{
		public:
			Font2D();
			Font2D(const std::string & face, unsigned int size);
			~Font2D();

			/**
			 * Enumeration of font style attributes
			 */
			typedef enum
			{
				STYLE_BOLD,		/**< Bold font style **/
				STYLE_ITALICS,	/**< Italics font style **/
				STYLE_UNDERLINE,/**< Underline font style **/
				STYLE_STRIKEOUT	/**< Strikeout font style **/
			} FontStyle;

			/**
			 * Set the font style attributes
			 * @param attribs the style attributes to set
			 */
			void style(unsigned int attribs);
			/**
			 * Get the style attributes
			 * @return the current style attributes
			 */
			unsigned int style(void) const;
			/**
			 * Get the font type size
			 * @return the type size
			 */
			int size(void) const;
			/**
			 * Set the font type size
			 * The font must be built after setting the size before the change will be visible.
			 * @param s the new font size
			 */
			void size(int s);
			/**
			 * Get the typeface of the font
			 * @return the name of the typeface
			 */
			std::string typeface(void) const;
			/**
			 * Set the font typeface
			 * The font must be built after setting the face name before the change will be visible.
			 * @param face the typeface
			 */
			void typeface(const std::string & face);
			/**
			 * Generate the GL objects necessary for the font with the current face and size.
			 * @return whether the font was build successfully
			 */
			bool build(void);
			/**
			 * Render the the text to the current drawing surface
			 * @param text the text to be printed
			 * @param x the left position to print
			 * @param y the top of the position to begin printing
			 */
			void print(const std::string & text, float x, float y);
			/**
			 * Get the width of the string
			 * @param str the string to get the width of
			 * @return the width
			 */
			unsigned int width(const std::string & str) const;
			/**
			 * Get the line height of the font
			 * @return the height
			 */
			unsigned int height(void) const;
			/**
			 * Get the width of a single character
			 * @param charcode the character to get the width of
			 * @return the width
			 */
			unsigned int width(unsigned char charcode) const;
			/**
			 * Access the underlying font character map texture
			 * @return a pointer to the texture
			 */
			boost::shared_ptr<Texture> texture(void) const;

		private:
			struct Glyph
			{
				
				float _x1;
				float _y1;
				float _x2;
				unsigned int _advance;
			};

			std::map<unsigned char, Glyph> _glyphs;
			boost::shared_ptr<Texture> _texture;

			float _tex_line_height; // _line
			unsigned int _line_height; // _height

			std::string _typeface;
			int _size;
			unsigned int _style;
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_FONT2D
