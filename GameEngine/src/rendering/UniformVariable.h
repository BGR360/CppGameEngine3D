#ifndef BENGINE_UNIFORM_VARIABLE_H
#define BENGINE_UNIFORM_VARIABLE_H

#include <Engine.h>

#include <string>

#include <rendering/OpenGL.h>

#include <math/Vector2.h>
#include <math/Vector3.h>
#include <math/Vector4.h>
#include <math/Matrix2x2.h>
#include <math/Matrix3x3.h>
#include <math/Matrix4x4.h>
#include <rendering/Texture.h>

using std::string;

using Math::Vector2;
using Math::Vector3;
using Math::Vector4;
using Math::Matrix2x2;
using Math::Matrix3x3;
using Math::Matrix4x4;
using Rendering::Texture;

namespace Rendering
{
	class ShaderProgram;

	class ENGINE_DLL_EXPORT IUniform
	{
	protected:
		string m_uniformName;
		GLuint m_uniformLocation;

	public:
		IUniform(string uniformName) : m_uniformName(uniformName), m_uniformLocation(-1) {}
		virtual ~IUniform() {}

		virtual void bind() = 0;

		inline void attachToShader(GLuint programID);
		
		inline string getName() const { return m_uniformName; }
		inline GLuint getLocation() const { return m_uniformLocation; }

		inline bool operator<(const IUniform& right) { return m_uniformName < right.getName(); }
	};

	template<typename T>
	class ENGINE_DLL_EXPORT UniformVariable : public IUniform
	{
		T m_uniformData;

	public:
		UniformVariable(string uniformName) : IUniform(uniformName), m_uniformData() {}
		virtual ~UniformVariable() {}

		inline void setData(const T& data);
		inline T& getData();
		
		virtual void bind();
	};

	//A specialization for UniformVariable<Texture>
	template<>
	class UniformVariable<Texture> : public UniformVariable<Texture*>
	{
	public:
		UniformVariable(const string& uniformName) : UniformVariable<Texture*>(uniformName) {}
	};

	#include "UniformVariable.inl"
}

#endif //BENGINE_UNIFORM_VARIABLE_H