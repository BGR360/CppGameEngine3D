#ifndef BENGINE_SHADER_COMPILING_EXCEPTION_H
#define BENGINE_SHADER_COMPILING_EXCEPTION_H

#include <Engine.h>

#include <glew/glew.h>

#include <exceptions/OpenGLException.h>

namespace Exceptions
{
	class ENGINE_DLL_EXPORT_IMPORT ShaderCompilingException : public OpenGLException
	{
		GLuint m_shaderID;
		string m_shaderName;
		string m_errorLog;

	public:
		ShaderCompilingException(GLuint shaderID = 0, string shaderName = "");
		virtual ~ShaderCompilingException();

		inline virtual const char* what() const throw()
		{
			return "ShaderCompilingException";
		}

		virtual string message() const throw();
	};
}

#endif //BENGINE_SHADER_COMPILING_EXCEPTION_H