#ifndef BENGINE_SHADER_H
#define BENGINE_SHADER_H

#include <rendering/OpenGL.h>

#include <string>

using std::string;

namespace Rendering
{
	class Shader
	{
	public:
		enum ShaderType
		{
			VERTEX_SHADER,
			TESS_CONTROL_SHADER,
			TESS_EVALUATION_SHADER,
			GEOMETRY_SHADER,
			FRAGMENT_SHADER,

			NUM_SHADER_TYPES
		};

	private:
		GLuint m_shaderID;
		ShaderType m_type;

	public:
		Shader(string filePath, ShaderType type);
		virtual ~Shader();

		GLuint getShaderID();
		ShaderType getShaderType();

	protected:
		void init(const string& filePath);
		void create();
		string loadShaderSource(const string& filePath);
		void compileShaderFromSource(const string& source);
		void destroy();
	};
}

#endif //BENGINE_SHADER_H