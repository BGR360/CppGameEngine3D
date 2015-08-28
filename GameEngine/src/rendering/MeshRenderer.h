#ifndef BENGINE_MESH_RENDERER_H
#define BENGINE_MESH_RENDERER_H

#include <Engine.h>

#include <rendering/OpenGL.h>
#include <core/component/RenderingComponent.h>

using Core::Component::RenderingComponent;

namespace Rendering
{
	class OpenGLMesh;
	class Material;

	class ENGINE_DLL_TESTING_ONLY MeshRenderer : public RenderingComponent
	{
		OpenGLMesh* m_mesh;
		Material* m_material;

	public:
		MeshRenderer(OpenGLMesh* mesh, Material* material);
		virtual ~MeshRenderer();

		virtual void render();

		OpenGLMesh* getMesh();
		Material* getMaterial();

		void setMesh(OpenGLMesh* mesh);
		void setMaterial(Material* material);
	};
}

#endif //BENGINE_MESH_RENDERER_H
