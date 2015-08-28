//For IUniform

void IUniform::attachToShader(GLuint programID)
{
	m_uniformLocation = glGetUniformLocation(programID, m_uniformName.c_str());
}


//For UniformVariable<T>

template<typename T>
void UniformVariable<T>::setData(const T& data)
{
	m_uniformData = data;
}

template<typename T>
T& UniformVariable<T>::getData()
{
	return m_uniformData;
}


//Template Instantiations for bind() (instantiations only, see .cpp for definitions)

template<> void UniformVariable<int>::bind();
template<> void UniformVariable<float>::bind();
template<> void UniformVariable<double>::bind();
template<> void UniformVariable<unsigned int>::bind();
template<> void UniformVariable<bool>::bind();
template<> void UniformVariable<Vector2>::bind();
template<> void UniformVariable<Vector3>::bind();
template<> void UniformVariable<Vector4>::bind();
template<> void UniformVariable<Matrix2x2>::bind();
template<> void UniformVariable<Matrix3x3>::bind();
template<> void UniformVariable<Matrix4x4>::bind();