#include "MeshRenderer.h"

#include <exceptions/ShaderCompilingException.h>
#include <rendering/OpenGLMesh.h>
#include <rendering/Material.h>
#include <rendering/ShaderProgram.h>

using Exceptions::ShaderCompilingException;

namespace Rendering
{
	MeshRenderer::MeshRenderer(OpenGLMesh* mesh, Material* material)
		: m_mesh(mesh), m_material(material) {}

	//THIS is where aaalll the magic happens.
	void MeshRenderer::render()
	{
		ShaderProgram* shader = m_material->getShader();

		//Update the "modelMatrix" uniform
		string modelMatrixStr("modelMatrix");
		if (!shader->hasUniform(modelMatrixStr))
		{
			//throw BengineException("The compiled shader is missing uniform 'modelMatrix'.");
		}
		else
		{
			shader->setUniform(
				"modelMatrix",
				getGameObject()->getTransform()->toModelMatrix());
		}

		//Bind the material
		m_material->bind();

		//Bind the Vertex Array
		GLuint vao = m_mesh->getVAO();
		glBindVertexArray(vao);

		//DrawElements
		glDrawElements(
			GL_TRIANGLES,
			m_mesh->getIndices().size(),
			GL_UNSIGNED_INT,
			0);

		//Unbind the Vertex Array
		glBindVertexArray(0);
	}

	OpenGLMesh* MeshRenderer::getMesh()
	{
		return m_mesh;
	}

	Material* MeshRenderer::getMaterial()
	{
		return m_material;
	}

	void MeshRenderer::setMesh(OpenGLMesh* mesh)
	{
		m_mesh = mesh;
	}

	void MeshRenderer::setMaterial(Material* material)
	{
		m_material = material;
	}

	MeshRenderer::~MeshRenderer()
	{
		
	}
}