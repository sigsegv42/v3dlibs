#ifndef INCLUDED_V3D_TEXTURE
#define INCLUDED_V3D_TEXTURE

#include "Image.h"

#include <boost/shared_ptr.hpp>

#include <string>

namespace v3D
{

	/**
	 * A OpenGL Texture object.
	 */
	class Texture
	{
		public:
			Texture();
			Texture(boost::shared_ptr<Image> image);
			Texture(const Texture &t);
			virtual ~Texture();

			Texture & operator = (const Texture & t);
			bool operator == (const Texture & t) const;

			/**
			 * Get whether the texture is set or not.
			 * @return true if the texture is not set, otherwise false.
			 */
			bool isnull(void);
			/**
			 * Make the texture active.
			 * @return true if successful otherwise false
			 */
			bool bind(void);
			/**
			 * Get whether the texture wraps (repeats)
			 * @return true if the texture wraps
			 */
			bool wrap(void) const;
			/**
			 * Set whether the texture wraps (repeats)
			 * @param repeat whether the texture should wrap
			 */
			void wrap(bool repeat);
			/**
			 * Get the width of the texture
			 * @return texture width
			 */
			unsigned int width(void) const;
			/**
			 * Get the height of the texture
			 * @return texture height
			 */
			unsigned int height(void) const;
			/**
			 * Create a texture from the source image
			 * @param image the texture source image
			 * @return true if the texture was sucessfully created
			 */
			bool create(boost::shared_ptr<Image> image);

			typedef enum 
			{ 
				NEAREST, 
				LINEAR, 
				MIPMAP, 
				UNKNOWN 
			} 
			TextureVersion;

		private:
			TextureVersion _type;
			unsigned int _texID;		// Texture ID Used To Select A Texture
			bool _wrap;		// Repeat(true) or Clamp(false)
			unsigned int _width;
			unsigned int _height;
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_TEXTURE
