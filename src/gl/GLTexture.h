#ifndef INCLUDED_V3D_GL_TEXTURE
#define INCLUDED_V3D_GL_TEXTURE

#include "../image/Texture.h"

namespace v3D
{

	/**
	 * A OpenGL Texture object.
	 */
	class GLTexture : public Texture
	{
		public:
			GLTexture();
			GLTexture(const Texture &t);
			virtual ~GLTexture();

			/**
			 * Make the texture active.
			 * @return true if successful otherwise false
			 */
			bool bind(void);
			/**
			 * Set whether the texture wraps (repeats)
			 * @param repeat whether the texture should wrap
			 */
			void wrap(bool repeat);
			/**
			 * Create a texture from the source image
			 * @param image the texture source image
			 * @return true if the texture was sucessfully created
			 */
			bool create(boost::shared_ptr<Image> image);
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_GL_TEXTURE
