#ifndef BENGINE_SHADER_PROGRAM_H
#define BENGINE_SHADER_PROGRAM_H

#include <Engine.h>

#include <vector>

#include <exceptions/BengineException.h>
#include <rendering/Shader.h>
#include <rendering/UniformVariable.h>
#include <util/Types.h>

using std::vector;

using Exceptions::BengineException;

namespace Rendering
{
	class ENGINE_DLL_EXPORT ShaderProgram;

	//We can keep track of the current shader
	ENGINE_DLL_EXPORT_IMPORT ShaderProgram* getCurrentShader();

	class ShaderProgram
	{
		GLuint m_programID;
		Shader* m_shaders[Shader::NUM_SHADER_TYPES]; //ShaderProgram has ownership of its shaders

		vector<IUniform*> m_uniforms;	//ShaderProgram does not have ownership of its UniformVariables

	public:
		ShaderProgram(string filePath);
		virtual ~ShaderProgram();

		template<typename T> inline void addUniform(const string& uniformName, const T& uniformData);
		template<typename T> inline void setUniform(const string& uniformName, const T& uniformData);

		void bind();
		GLuint getProgramID() const;
		uint getNumUniforms() const;
		uint findUniform(const string& uniformName) const;
		bool hasUniform(const string& uniformName) const;
		IUniform* getUniform(const string& uniformName);

	protected:
		virtual void init(const string& filePath);
		Shader* addShader(Shader* shader);
		void create();
		void link();
		void validate();
		void detectUniforms();
		template<typename T> inline void addUniform(const string& uniformName);
		void destroy();
	};


	template<typename T>
	void ShaderProgram::addUniform(const string& uniformName)
	{
		UniformVariable<T>* uniform = new UniformVariable<T>(uniformName);
		uniform->attachToShader(this->getProgramID());
		m_uniforms.push_back(uniform);
	}

	template<typename T>
	void ShaderProgram::addUniform(const string& uniformName, const T& uniformData)
	{
		UniformVariable<T>* uniform = new UniformVariable<T>(uniformName);
		uniform->attachToShader(this->getProgramID());
		uniform->setData(uniformData);

		m_uniforms.push_back(uniform);
	}

	template<typename T>
	void ShaderProgram::setUniform(const string& uniformName, const T& uniformData)
	{
		IUniform* iuniform = this->getUniform(uniformName);

		if (iuniform == 0)
		{
			string message = "This ShaderProgram does not have an IUniform with name '";
			message += uniformName;
			message += "'.";
			throw BengineException(message);
		}

		UniformVariable<T>* uniform = dynamic_cast<UniformVariable<T>*>(iuniform);

		if (uniform == 0)
		{
			string message = "Invalid type conversion for UniformVariable<T> with name '";
			message += uniformName;
			message += "'.";
			throw BengineException(message);
		}

		uniform->setData(uniformData);
	}
}

#endif //BENGINE_SHADER_PROGRAM_H