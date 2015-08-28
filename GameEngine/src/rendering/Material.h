#ifndef BENGINE_MATERIAL_H
#define BENGINE_MATERIAL_H

#include <Engine.h>

namespace Rendering
{
	class ShaderProgram;
	class Texture;

	class ENGINE_DLL_EXPORT_IMPORT Material
	{
		ShaderProgram* m_shader;
		Texture* m_texture;

	public:
		Material(ShaderProgram* shader, Texture* texture);
		virtual ~Material();

		void bind();

		ShaderProgram* getShader();
		Texture* getTexture();

		void setShader(ShaderProgram* shader);
		void setTexture(Texture* texture);
	};
}

#endif //BENGINE_MATERIAL_H