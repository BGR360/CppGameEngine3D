#ifndef BENGINE_SHADER_LINKING_EXCEPTION_H
#define BENGINE_SHADER_LINKING_EXCEPTION_H

#include <Engine.h>

#include <exceptions/OpenGLException.h>
#include <rendering/ShaderProgram.h>

using Rendering::ShaderProgram;

namespace Exceptions
{
	class ENGINE_DLL_EXPORT_IMPORT ShaderLinkingException : public OpenGLException
	{
		GLuint m_programID;
		string m_programName;
		string m_errorLog;

	public:
		ShaderLinkingException();
		ShaderLinkingException(ShaderProgram* program, string programName = "");
		virtual ~ShaderLinkingException();

		inline virtual const char* what() const throw()
		{
			return "ShaderLinkingException";
		}

		virtual string message() const throw();
	};
}

#endif //BENGINE_SHADER_LINKING_EXCEPTION_H