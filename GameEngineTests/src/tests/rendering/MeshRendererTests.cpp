#include <Testing.h>

#include <core/GameObject.h>
#include <resources/ResourceManager.h>
#include <rendering/Material.h>
#include <rendering/MeshRenderer.h>
#include <rendering/ShaderProgram.h>

using Core::GameObject;
using Resources::ResourceManager;
using Rendering::MeshRenderer;

#ifdef RENDERING_TESTS

TEST(MeshRenderer, AddToGameObject)
{
	ResourceManager resourceManager;
	resourceManager.loadMesh("./res/meshes/testCube.obj");

	ShaderProgram shader("./res/shaders/testShader");
	Material* material = new Material(&shader, 0);

	GameObject gameObject;
	gameObject.addComponent(new MeshRenderer(
		resourceManager.getMesh("testCube"),
		material));

	int expectedNumComponents = 1;
	int actualNumComponents = gameObject.getNumComponents();

	EXPECT_EQ(expectedNumComponents, actualNumComponents);

	MeshRenderer* meshRenderer = gameObject.getComponent<MeshRenderer>();

	GameObject* expectedPtr = &gameObject;
	GameObject* actualPtr = meshRenderer->getGameObject();

	EXPECT_EQ(expectedPtr, actualPtr);

	delete material;
}

#endif //RENDERING_TESTS