#ifndef BENGINE_OPEN_GL_EXCEPTION_H
#define BENGINE_OPEN_GL_EXCEPTION_H

#include <Engine.h>

#include <exceptions/BengineException.h>

using Exceptions::BengineException;

namespace Exceptions
{
	class ENGINE_DLL_EXPORT_IMPORT OpenGLException : public BengineException
	{
	public:
		OpenGLException()
			: BengineException("An OpenGL error occurred.") {}
		OpenGLException(string message)
			: BengineException(message) {}
		virtual ~OpenGLException() {}

		inline virtual const char* what() const throw()		
		{
			return "OpenGLException";
		}
	};
}

#endif //BENGINE_OPEN_GL_EXCEPTION_H