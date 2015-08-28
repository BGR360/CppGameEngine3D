#include "Material.h"

#include <rendering/ShaderProgram.h>
#include <rendering/Texture.h>

namespace Rendering
{
	Material::Material(ShaderProgram* shader, Texture* texture)
		: m_shader(shader), m_texture(texture) {}

	void Material::bind()
	{
		if (m_shader != 0)
		{
			m_shader->bind();

			if (m_texture != 0)
			{
				m_texture->bind();
			}
			else
			{
				//TODO: exception
			}
		}
		else
		{
			//TODO: exception
		}
	}

	ShaderProgram* Material::getShader()
	{
		return m_shader;
	}

	Texture* Material::getTexture()
	{
		return m_texture;
	}

	void Material::setShader(ShaderProgram* shader)
	{
		m_shader = shader;
	}

	void Material::setTexture(Texture* texture)
	{
		m_texture = texture;
	}

	Material::~Material() {}
}