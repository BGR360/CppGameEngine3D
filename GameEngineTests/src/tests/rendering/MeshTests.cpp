#include <Testing.h>

#include <iostream>

#include <exceptions/BengineException.h>
#include <math/Vector2.h>
#include <math/Vector3.h>
#include <rendering/Mesh.h>
#include <rendering/OpenGLMesh.h>
#include <resources/ResourceManager.h>

using Exceptions::BengineException;
using Rendering::Mesh;
using Rendering::OpenGLMesh;
using Resources::ResourceManager;

#ifdef RENDERING_TESTS

TEST(Mesh, LoadMesh)
{
	try
	{
		ResourceManager resourceManager;

		OpenGLMesh* mesh = resourceManager.loadMesh("./res/meshes/testCube.obj");

		Vector3 expected_positions[24] =
		{
			Vector3(-0.5f, -0.5f, -0.5f),
			Vector3(+0.5f, -0.5f, -0.5f),
			Vector3(+0.5f, +0.5f, -0.5f),
			Vector3(-0.5f, +0.5f, -0.5f),

			Vector3(-0.5f, -0.5f, +0.5f),
			Vector3(-0.5f, -0.5f, -0.5f),
			Vector3(-0.5f, +0.5f, -0.5f),
			Vector3(-0.5f, +0.5f, +0.5f),

			Vector3(+0.5f, -0.5f, +0.5f),
			Vector3(-0.5f, -0.5f, +0.5f),
			Vector3(-0.5f, +0.5f, +0.5f),
			Vector3(+0.5f, +0.5f, +0.5f),

			Vector3(+0.5f, +0.5f, +0.5f),
			Vector3(+0.5f, +0.5f, -0.5f),
			Vector3(+0.5f, -0.5f, -0.5f),
			Vector3(+0.5f, -0.5f, +0.5f),

			Vector3(-0.5f, -0.5f, +0.5f),
			Vector3(+0.5f, -0.5f, +0.5f),
			Vector3(+0.5f, -0.5f, -0.5f),
			Vector3(-0.5f, -0.5f, -0.5f),

			Vector3(-0.5f, +0.5f, -0.5f),
			Vector3(+0.5f, +0.5f, -0.5f),
			Vector3(+0.5f, +0.5f, +0.5f),
			Vector3(-0.5f, +0.5f, +0.5f),
		};

		Vector2 expected_uvCoords[24] =
		{
			Vector2(1.0f, 0.0f),
			Vector2(1.0f, 1.0f),
			Vector2(0.0f, 1.0f),
			Vector2(0.0f, 0.0f),

			Vector2(1.0f, 0.0f),
			Vector2(1.0f, 1.0f),
			Vector2(0.0f, 1.0f),
			Vector2(0.0f, 0.0f),

			Vector2(1.0f, 0.0f),
			Vector2(1.0f, 1.0f),
			Vector2(0.0f, 1.0f),
			Vector2(0.0f, 0.0f),

			Vector2(1.0f, 0.0f),
			Vector2(1.0f, 1.0f),
			Vector2(0.0f, 1.0f),
			Vector2(0.0f, 0.0f),

			Vector2(0.0f, 0.0f),
			Vector2(0.0f, 1.0f),
			Vector2(1.0f, 1.0f),
			Vector2(1.0f, 0.0f),

			Vector2(0.0f, 0.0f),
			Vector2(0.0f, 1.0f),
			Vector2(1.0f, 1.0f),
			Vector2(1.0f, 0.0f),
		};

		Vector3 expected_normals[24] =
		{
			Vector3(+0.0f, +0.0f, -1.0f),
			Vector3(+0.0f, +0.0f, -1.0f),
			Vector3(+0.0f, +0.0f, -1.0f),
			Vector3(+0.0f, +0.0f, -1.0f),

			Vector3(-1.0f, +0.0f, +0.0f),
			Vector3(-1.0f, +0.0f, +0.0f),
			Vector3(-1.0f, +0.0f, +0.0f),
			Vector3(-1.0f, +0.0f, +0.0f),

			Vector3(+0.0f, +0.0f, +1.0f),
			Vector3(+0.0f, +0.0f, +1.0f),
			Vector3(+0.0f, +0.0f, +1.0f),
			Vector3(+0.0f, +0.0f, +1.0f),

			Vector3(+1.0f, +0.0f, +0.0f),
			Vector3(+1.0f, +0.0f, +0.0f),
			Vector3(+1.0f, +0.0f, +0.0f),
			Vector3(+1.0f, +0.0f, +0.0f),

			Vector3(+0.0f, -1.0f, +0.0f),
			Vector3(+0.0f, -1.0f, +0.0f),
			Vector3(+0.0f, -1.0f, +0.0f),
			Vector3(+0.0f, -1.0f, +0.0f),

			Vector3(+0.0f, +1.0f, +0.0f),
			Vector3(+0.0f, +1.0f, +0.0f),
			Vector3(+0.0f, +1.0f, +0.0f),
			Vector3(+0.0f, +1.0f, +0.0f),
		};

		uint expected_indices[36] =
		{
			0, 1, 2, 0, 2, 3,
			4, 5, 6, 4, 6, 7,
			8, 9, 10, 8, 10, 11,
			12, 13, 14, 12, 14, 15,
			16, 17, 18, 16, 18, 19,
			20, 21, 22, 20, 22, 23
		};

		EXPECT_FALSE(mesh == 0);

		if (mesh != 0)
		{
			vector<Vector3> actual_positions = mesh->getPositions();
			vector<Vector2> actual_uvCoords = mesh->getUvCoords();
			vector<Vector3> actual_normals = mesh->getNormals();
			vector<uint> actual_indices = mesh->getIndices();

			EXPECT_EQ(24, actual_positions.size());
			EXPECT_EQ(24, actual_uvCoords.size());
			EXPECT_EQ(24, actual_normals.size());
			EXPECT_EQ(36, actual_indices.size());

			if (actual_positions.size() == 24
				&& actual_uvCoords.size() == 24
				&& actual_normals.size() == 24
				&& actual_indices.size() == 36)
			{
				for (uint i = 0; i < 24; i++)
				{
					EXPECT_VEC3_EQ(expected_positions[i], actual_positions[i]);
				}
				for (uint i = 0; i < 24; i++)
				{
					EXPECT_VEC2_EQ(expected_uvCoords[i], actual_uvCoords[i]);
				}
				for (uint i = 0; i < 24; i++)
				{
					EXPECT_VEC3_EQ(expected_normals[i], actual_normals[i]);
				}
				for (uint i = 0; i < 36; i++)
				{
					EXPECT_EQ(expected_indices[i], actual_indices[i]);
				}
			}
		}
	}
	catch (BengineException& e)
	{
		std::cout << "Caught: " << e.what() << ": " << e.message() << std::endl;
	}
}

TEST(Mesh, GetMesh)
{
	ResourceManager resourceManager;

	OpenGLMesh* loadedMesh = resourceManager.loadMesh("./res/meshes/testCube.obj");
	OpenGLMesh* gottenMesh = resourceManager.getMesh("testCube");

	EXPECT_EQ(loadedMesh, gottenMesh);
}
#endif //RENDERING_TESTS
