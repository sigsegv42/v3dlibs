/**
 * (c) Joshua Farr <j.wgasa@gmail.com>
 *
 */

#pragma once

#include <string>

namespace v3D
{

	/**
	 * A GLSL shader
	 */
	class Shader
	{
		public:
			typedef enum
			{
				SHADER_TYPE_FRAGMENT = 2,
				SHADER_TYPE_VERTEX = 4
			} ShaderType;

			/**
			 * Create a new GLSL shader
			 */
			Shader(ShaderType type, const std::string & shader);
			~Shader();

			/**
			 * Attach the shader to a shader program
			 */
			void attach(unsigned int program);
			/**
			 * Detach the shader from a shader program
			 */
			void detach(unsigned int program);

		private:
			ShaderType type_;
			unsigned int id_;
	};

}; // end namespace v3D
