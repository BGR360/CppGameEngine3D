#ifndef BENGINE_OPEN_GL_H
#define BENGINE_OPEN_GL_H

#include <string>
using std::string;

#include <Engine.h>

#include <glew/glew.h>

#include <exceptions/OpenGLException.h>
using Exceptions::OpenGLException;

void ENGINE_DLL_EXPORT_IMPORT glCheckError(string functionName = "");

#define glCheckCall(glFunction) \
	glFunction; \
	glCheckError(#glFunction)

#endif //BENGINE_OPEN_GL_H

