#include "Shader.h"

#include <fstream>

#include <exceptions/FileNotFoundException.h>
#include <exceptions/ShaderCompilingException.h>

#include <util/Types.h>

using std::ifstream;
using std::getline;

using Exceptions::FileNotFoundException;
using Exceptions::ShaderCompilingException;

namespace Rendering
{
	Shader::Shader(string filePath, ShaderType type)
		: m_shaderID(0), m_type(type)
	{
		this->init(filePath);
	}

	GLuint Shader::getShaderID()
	{
		return m_shaderID;
	}

	Shader::ShaderType Shader::getShaderType()
	{
		return m_type;
	}

	void Shader::init(const string& filePath)
	{
		this->create();
		string shaderSource = this->loadShaderSource(filePath);
		this->compileShaderFromSource(shaderSource);
	}

	void Shader::create()
	{
		switch (m_type)
		{
		case VERTEX_SHADER:
			m_shaderID = glCreateShader(GL_VERTEX_SHADER);
			break;

		case TESS_CONTROL_SHADER:
			m_shaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
			break;

		case TESS_EVALUATION_SHADER:
			m_shaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);
			break;

		case GEOMETRY_SHADER:
			m_shaderID = glCreateShader(GL_GEOMETRY_SHADER);
			break;

		case FRAGMENT_SHADER:
			m_shaderID = glCreateShader(GL_FRAGMENT_SHADER);
			break;

		default:
			m_shaderID = -1;
			break;
		}

		if (m_shaderID == -1)
		{
			throw ShaderCompilingException();
		}
	}

	string Shader::loadShaderSource(const string& filePath)
	{
		ifstream file;
		file.open((filePath).c_str());

		string output;
		string line;

		if (file.is_open())
		{
			while (file.good())
			{
				getline(file, line);
				output.append(line + "\n");
			}
		}
		else
		{
			throw FileNotFoundException(filePath);
		}

		return output;
	}

	void Shader::compileShaderFromSource(const string& source)
	{
		const char* src = source.c_str();
		glShaderSource(m_shaderID, 1, &src, 0);
		glCompileShader(m_shaderID);

		//Throw exception if compilation failed
		GLint compileStatus;
		glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &compileStatus);

		if (compileStatus != GL_TRUE)
		{
			throw ShaderCompilingException(m_shaderID);
		}
	}

	void Shader::destroy()
	{
		glDeleteShader(m_shaderID);
	}

	Shader::~Shader()
	{
		this->destroy();
	}
}