#include "ShaderProgram.h"

#include <exceptions/ShaderLinkingException.h>
#include <util/Types.h>

using Exceptions::ShaderLinkingException;

namespace Rendering
{
	//One global pointer to the currently bound shader
	ShaderProgram* CURRENT_SHADER = 0;

	ShaderProgram* getCurrentShader()
	{
		return CURRENT_SHADER;
	}

	ShaderProgram::ShaderProgram(string filePath)
		: m_programID(-1), m_uniforms()
	{
		for (uint i = 0; i < Shader::NUM_SHADER_TYPES; i++)
		{
			m_shaders[i] = 0;
		}
		this->init(filePath);
	}

	void ShaderProgram::bind()
	{
		CURRENT_SHADER = this;

		//Bind the program
		glUseProgram(m_programID);

		//Bind all the uniforms
		vector<IUniform*>::iterator i;
		for (i = m_uniforms.begin(); i != m_uniforms.end(); i++)
		{
			(*i)->bind();
		}
	}

	GLuint ShaderProgram::getProgramID() const
	{
		return m_programID;
	}

	uint ShaderProgram::getNumUniforms() const
	{
		return m_uniforms.size();
	}

	//A linear search to find an IUniform with a particular name. Returns m_uniforms.size() if none found
	uint ShaderProgram::findUniform(const string& uniformName) const
	{
		string currentName;
		uint index;
		for (index = 0; index < m_uniforms.size(); index++)
		{
			currentName = m_uniforms[index]->getName();
			if (currentName.compare(uniformName) == 0)
			{
				return index;
			}
		}
		return index;
	}

	bool ShaderProgram::hasUniform(const string& uniformName) const
	{
		return this->findUniform(uniformName) != getNumUniforms();
	}

	IUniform* ShaderProgram::getUniform(const string& uniformName)
	{
		uint index = findUniform(uniformName);
		if (index < m_uniforms.size())
		{
			return m_uniforms[index];
		}
		else
		{
			return 0;
		}
	}

	void ShaderProgram::init(const string& filePath)
	{
		this->create();

		this->addShader(new Shader(filePath + ".vs", Shader::VERTEX_SHADER));
		this->addShader(new Shader(filePath + ".fs", Shader::FRAGMENT_SHADER));

		this->link();
		this->validate();
		this->detectUniforms();
	}


	//Returns the address of the shader just added
	Shader* ShaderProgram::addShader(Shader* shader)
	{
		Shader::ShaderType shaderType = shader->getShaderType();

		m_shaders[shaderType] = shader;

		return shader;
	}

	void ShaderProgram::create()
	{
		m_programID = glCreateProgram();
	}

	void ShaderProgram::link()
	{
		//Attach all of our shaders to the program object
		for (uint i = 0; i < Shader::NUM_SHADER_TYPES; i++)
		{
			Shader* shader = m_shaders[i];
			if (shader != 0)
			{
				glAttachShader(m_programID, shader->getShaderID());
			}
		}

		//And link
		glLinkProgram(m_programID);

		//Throw exception if failed
		GLint linkStatus;
		glGetProgramiv(m_programID, GL_LINK_STATUS, &linkStatus);

		if (linkStatus != GL_TRUE)
		{
			throw ShaderLinkingException(this);
		}
	}

	void ShaderProgram::validate()
	{
		glValidateProgram(m_programID);

		GLint validateStatus;
		glGetProgramiv(m_programID, GL_LINK_STATUS, &validateStatus);

		if (validateStatus != GL_TRUE)
		{
			throw ShaderLinkingException(this);
		}
	}

	void ShaderProgram::detectUniforms()
	{
		GLint numActiveUniforms;
		glCheckCall(glGetProgramiv(m_programID, GL_ACTIVE_UNIFORMS, &numActiveUniforms));

		for (uint i = 0; i < (uint)numActiveUniforms; i++)
		{
			GLint nameLength;
			glCheckCall(glGetActiveUniformsiv(m_programID, 1, &i, GL_UNIFORM_NAME_LENGTH, &nameLength));

			GLchar* uniformName = new GLchar[nameLength];
			glCheckCall(glGetActiveUniformName(m_programID, i, nameLength, 0, uniformName));

			GLint uniformType;
			glCheckCall(glGetActiveUniformsiv(m_programID, 1, &i, GL_UNIFORM_TYPE, &uniformType));

			GLenum type = (GLenum)uniformType;

			switch (type)
			{
			case GL_FLOAT:
				this->addUniform<float>(uniformName);
				break;
			case GL_FLOAT_VEC2:
				this->addUniform<Vector2>(uniformName);
				break;
			case GL_FLOAT_VEC3:
				this->addUniform<Vector3>(uniformName);
				break;
			case GL_FLOAT_VEC4:
				this->addUniform<Vector4>(uniformName);
				break;
			case GL_DOUBLE:
				this->addUniform<double>(uniformName);
				break;
			case GL_INT:
				this->addUniform<int>(uniformName);
				break;
			case GL_UNSIGNED_INT:
				this->addUniform<uint>(uniformName);
				break;
			case GL_BOOL:
				this->addUniform<bool>(uniformName);
				break;
			case GL_FLOAT_MAT2:
				this->addUniform<Matrix2x2>(uniformName);
				break;
			case GL_FLOAT_MAT3:
				this->addUniform<Matrix3x3>(uniformName);
				break;
			case GL_FLOAT_MAT4:
				this->addUniform<Matrix4x4>(uniformName);
				break;
			case GL_SAMPLER_1D:
				break;
			case GL_SAMPLER_2D:
				this->addUniform<Texture>(uniformName);
				break;
			case GL_SAMPLER_3D:
				break;
			default:
				break;
			}

			delete uniformName;
		}
	}

	void ShaderProgram::destroy()
	{
		//Destroy all the Shaders
		for (uint i = 0; i < Shader::NUM_SHADER_TYPES; i++)
		{
			Shader* shader = m_shaders[i];
			if (shader != 0)
			{
				delete shader;
			}
		}

		//Destroy all the UniformVariables
		for (uint i = 0; i < m_uniforms.size(); i++)
		{
			IUniform* uniform = m_uniforms[i];
			if (uniform != 0)
			{
				delete uniform;
			}
		}

		m_uniforms.clear();

		//Destroy the program object
		glDeleteProgram(m_programID);
	}

	ShaderProgram::~ShaderProgram()
	{
		this->destroy();
	}
}