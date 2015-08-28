#include "ShaderCompilingException.h"

namespace Exceptions
{
	ShaderCompilingException::ShaderCompilingException(GLuint shaderID, string shaderName)
		: m_shaderID(shaderID), m_shaderName(shaderName), m_errorLog("")
	{
		if (m_shaderID != 0)
		{
			GLint infoLogSize;
			glGetShaderiv(m_shaderID, GL_INFO_LOG_LENGTH, &infoLogSize);

			GLint length;
			GLchar* infoLog = new GLchar[infoLogSize];
			glGetShaderInfoLog(m_shaderID, infoLogSize, &length, infoLog);

			m_errorLog = string(infoLog);

			delete[] infoLog;
		}
	}

	string ShaderCompilingException::message() const throw()
	{
		string ret = "Failed to compile shader";
		
		if (m_shaderName.compare("") != 0)
		{
			ret += ' ';
			ret += m_shaderName;
		}
		else
		{
			ret += '.';
		}

		if (m_errorLog.compare("") != 0)
		{
			ret += "\nError Log:\n";
			ret += m_errorLog;
		}

		return ret;
	}

	ShaderCompilingException::~ShaderCompilingException() {}
}