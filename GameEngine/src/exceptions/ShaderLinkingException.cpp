#include "ShaderLinkingException.h"

namespace Exceptions
{
	ShaderLinkingException::ShaderLinkingException()
		: m_programID(0), m_programName(""), m_errorLog("")
	{}

	ShaderLinkingException::ShaderLinkingException(ShaderProgram* program, string programName)
		: m_programID(program->getProgramID()), m_programName(programName), m_errorLog("")
	{
		if (m_programID != 0)
		{
			GLint infoLogSize;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogSize);

			GLint length;
			GLchar* infoLog = new GLchar[infoLogSize];
			glCheckCall(glGetProgramInfoLog(m_programID, infoLogSize, &length, infoLog));

			m_errorLog = string(infoLog);

			delete[] infoLog;
		}
	}

	string ShaderLinkingException::message() const throw()
	{
		string ret = "Failed to link shader program";

		if (m_programName.compare("") != 0)
		{
			ret += ' ';
			ret += m_programName;
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

	ShaderLinkingException::~ShaderLinkingException() {}
}