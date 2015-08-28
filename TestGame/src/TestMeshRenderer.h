#ifndef TESTGAME_TEST_MESH_RENDERER_H
#define TESTGAME_TEST_MESH_RENDERER_H

#include <rendering/MeshRenderer.h>
using Rendering::MeshRenderer;

#include "TestComponent.h"

class TestMeshRenderer : public MeshRenderer
{
public:
	TestMeshRenderer(OpenGLMesh* mesh, ShaderProgram* shader) : MeshRenderer(mesh, shader) {}
	virtual void render()
	{
		MeshRenderer::render();
	}
};

#endif //TESTGAME_TEST_MESH_RENDERER_H