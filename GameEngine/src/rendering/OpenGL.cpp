#include "OpenGL.h"

void glCheckError(string functionName)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		string message = "OpenGL function call ";
		if (functionName.compare("") != 0)
		{
			message += functionName;
			message += ' ';
		}
		message += "caused OpenGL error: ";

		switch (error)
		{
		case GL_INVALID_ENUM:
			message += "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			message += "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			message += "GL_INVALID_OPERATION";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			message += "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		case GL_OUT_OF_MEMORY:
			message += "GL_OUT_OF_MEMORY";
			break;
		case GL_STACK_UNDERFLOW:
			message += "GL_STACK_UNDERFLOW";
			break;
		case GL_STACK_OVERFLOW:
			message += "GL_STACK_OVERFLOW";
			break;
		default:
			break;
		}

		throw OpenGLException(message);
	}
}