#include <Testing.h>

#include <iostream>

#include <exceptions/BengineException.h>
#include <rendering/Mesh.h>
#include <resources/ObjFile.h>
#include <util/filesys/FileSystem.h>

using Exceptions::BengineException;
using Resources::ObjFile;
using Resources::ObjFace;
using Resources::ObjVertex;
using Util::FileSystem;

TEST(ObjFile, OpenClose)
{
	//Testing when file not open from constructor
	ObjFile objFile;
	EXPECT_FALSE(objFile.isOpen());
	objFile.open(FileSystem::getInstance().path("./res/meshes/testCube.obj"));
	EXPECT_TRUE(objFile.isOpen());
	objFile.close();
	EXPECT_FALSE(objFile.isOpen());

	//Testing when file is open from constructor
	ObjFile objFile2(FileSystem::getInstance().path("./res/meshes/testCube.obj"));
	EXPECT_FALSE(objFile2.isOpen());
	objFile2.open();
	EXPECT_TRUE(objFile2.isOpen());
	objFile2.close();
	EXPECT_FALSE(objFile2.isOpen());
}

TEST(ObjFile, OpenWithoutFilePath)
{
	ObjFile objFile;
	EXPECT_ANY_THROW(objFile.open());
}

TEST(ObjFile, OpenWhenOpen)
{
	ObjFile objFile(FileSystem::getInstance().path("./res/meshes/testCube.obj"));
	objFile.open();
	EXPECT_ANY_THROW(objFile.open());
}

TEST(ObjFile, CloseWhenClosed)
{
	ObjFile objFile;
	EXPECT_ANY_THROW(objFile.close());
}

TEST(ObjFile, FileNotFound)
{
	ObjFile objFile(FileSystem::getInstance().path("a;ldkfivnae;jivkn,"));
	EXPECT_ANY_THROW(objFile.open());
}



Vector3 expected_v[8] =
{
	Vector3(-0.5f, -0.5f, -0.5f),
	Vector3(+0.5f, -0.5f, -0.5f),
	Vector3(+0.5f, +0.5f, -0.5f),
	Vector3(-0.5f, +0.5f, -0.5f),
	Vector3(-0.5f, -0.5f, +0.5f),
	Vector3(+0.5f, -0.5f, +0.5f),
	Vector3(+0.5f, +0.5f, +0.5f),
	Vector3(-0.5f, +0.5f, +0.5f)
};

Vector2 expected_vt[4] =
{
	Vector2(0.0f, 0.0f),
	Vector2(0.0f, 1.0f),
	Vector2(1.0f, 1.0f),
	Vector2(1.0f, 0.0f)
};

Vector3 expected_vn[6] =
{
	Vector3(+0.0f, +0.0f, -1.0f),
	Vector3(-1.0f, +0.0f, +0.0f),
	Vector3(+0.0f, +0.0f, +1.0f),
	Vector3(+1.0f, +0.0f, +0.0f),
	Vector3(+0.0f, -1.0f, +0.0f),
	Vector3(+0.0f, +1.0f, +0.0f)
};

ObjVertex expected_vertices[24] =
{
	1, 4, 1,	2, 3, 1,	3, 2, 1,	4, 1, 1,
	5, 4, 2,	1, 3, 2,	4, 2, 2,	8, 1, 2,
	6, 4, 3,	5, 3, 3,	8, 2, 3,	7, 1, 3,
	7, 4, 4,	3, 3, 4,	2, 2, 4,	6, 1, 4,
	5, 1, 5,	6, 2, 5,	2, 3, 5,	1, 4, 5,
	4, 1, 6,	3, 2, 6,	7, 3, 6,	8, 4, 6
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

ObjVertex expected_vertices_only_verts[8] =
{
	1, -1, -1,	2, -1, -1,	3, -1, -1,	4, -1, -1,
	5, -1, -1,	8, -1, -1,	6, -1, -1,	7, -1, -1
};

uint expected_indices_only_verts[36] =
{
	0, 1, 2, 0, 2, 3,
	4, 0, 3, 4, 3, 7,
	5, 4, 7, 5, 7, 6,
	6, 2, 1, 6, 1, 5,
	4, 5, 1, 4, 1, 0,
	3, 2, 6, 3, 6, 7
};

inline void expect_objFile_eq(ObjFile& objFile)
{
	vector<Vector3> actual_v = objFile.get_v_list();
	vector<Vector2> actual_vt = objFile.get_vt_list();
	vector<Vector3> actual_vn = objFile.get_vn_list();
	vector<ObjVertex> actual_vertices = objFile.getVertices();
	vector<uint> actual_indices = objFile.getIndices();

	uint v_size = sizeof(expected_v) / sizeof(Vector3);
	uint vt_size = sizeof(expected_vt) / sizeof(Vector2);
	uint vn_size = sizeof(expected_vn) / sizeof(Vector3);
	uint vertices_size = sizeof(expected_vertices) / sizeof(ObjVertex);
	uint indices_size = sizeof(expected_indices) / sizeof(uint);

	bool v_size_b = v_size == actual_v.size();
	bool vt_size_b = vt_size == actual_vt.size();
	bool vn_size_b = vn_size == actual_vn.size();
	bool vertices_size_b = vertices_size == actual_vertices.size();
	bool indices_size_b = indices_size == actual_indices.size();

	EXPECT_EQ(v_size, actual_v.size());
	EXPECT_EQ(vt_size, actual_vt.size());
	EXPECT_EQ(vn_size, actual_vn.size());
	EXPECT_EQ(vertices_size, actual_vertices.size());
	EXPECT_EQ(indices_size, actual_indices.size());

	EXPECT_TRUE(objFile.hasTextureCoordinates());
	EXPECT_TRUE(objFile.hasNormals());

	if (v_size_b && vt_size_b && vn_size_b && vertices_size_b && indices_size_b)
	{
		for (uint i = 0; i < v_size; i++)
		{
			EXPECT_VEC3_EQ(expected_v[i], actual_v[i]);
		}
		for (uint i = 0; i < vt_size; i++)
		{
			EXPECT_VEC2_EQ(expected_vt[i], actual_vt[i]);
		}
		for (uint i = 0; i < vn_size; i++)
		{
			EXPECT_VEC3_EQ(expected_vn[i], actual_vn[i]);
		}
		for (uint i = 0; i < vertices_size; i++)
		{
			EXPECT_EQ(expected_vertices[i], actual_vertices[i]);
		}
		for (uint i = 0; i < indices_size; i++)
		{
			EXPECT_EQ(expected_indices[i], actual_indices[i]);
		}
	}
}

inline void expect_objFile_eq_only_verts(ObjFile& objFile)
{
	vector<Vector3> actual_v = objFile.get_v_list();
	vector<Vector2> actual_vt = objFile.get_vt_list();
	vector<Vector3> actual_vn = objFile.get_vn_list();
	vector<ObjVertex> actual_vertices = objFile.getVertices();
	vector<uint> actual_indices = objFile.getIndices();

	uint v_size = sizeof(expected_v) / sizeof(Vector3);
	uint vt_size = 0;
	uint vn_size = 0;
	uint vertices_size = sizeof(expected_vertices_only_verts) / sizeof(ObjVertex);
	uint indices_size = sizeof(expected_indices_only_verts) / sizeof(uint);

	bool v_size_b = v_size == actual_v.size();
	bool vt_size_b = vt_size == actual_vt.size();
	bool vn_size_b = vn_size == actual_vn.size();
	bool vertices_size_b = vertices_size == actual_vertices.size();
	bool indices_size_b = indices_size == actual_indices.size();

	EXPECT_EQ(v_size, actual_v.size());
	EXPECT_EQ(vt_size, actual_vt.size());
	EXPECT_EQ(vn_size, actual_vn.size());
	EXPECT_EQ(vertices_size, actual_vertices.size());
	EXPECT_EQ(indices_size, actual_indices.size());

	if (v_size_b && vt_size_b && vn_size_b && vertices_size_b && indices_size_b)
	{
		for (uint i = 0; i < v_size; i++)
		{
			EXPECT_VEC3_EQ(expected_v[i], actual_v[i]);
		}
		for (uint i = 0; i < vt_size; i++)
		{
			EXPECT_VEC2_EQ(expected_vt[i], actual_vt[i]);
		}
		for (uint i = 0; i < vn_size; i++)
		{
			EXPECT_VEC3_EQ(expected_vn[i], actual_vn[i]);
		}
		for (uint i = 0; i < vertices_size; i++)
		{
			EXPECT_EQ(expected_vertices_only_verts[i], actual_vertices[i]);
		}
		for (uint i = 0; i < indices_size; i++)
		{
			uint index = actual_indices[i];
			ObjVertex indexedVert = actual_vertices[index];
			uint actual_index = indexedVert.v_index - 1;
			EXPECT_EQ(expected_indices_only_verts[i], actual_index);

			if (actual_index != expected_indices_only_verts[i])
			{
				cout << "i=" << i << endl;
				cout << "actual_indices[i]=" << actual_indices[i] << endl;
			}
		}
	}
}

TEST(ObjFile, LoadFile)
{
	try
	{
		ObjFile objFile(FileSystem::getInstance().path("./res/meshes/testCube.obj"));
		objFile.open();

		expect_objFile_eq(objFile);

		objFile.close();
	}
	catch (BengineException& e)
	{
		std::cout << "caught: " << e.what()
			<< ": " << e.message() << std::endl;

		GTEST_FAIL();
	}
}

TEST(ObjFile, LoadFileWithQuadFaces)
{
	try
	{
		ObjFile objFile;
		objFile.open(FileSystem::getInstance().path("./res/meshes/testCubeQuads.obj"));

		expect_objFile_eq(objFile);

		objFile.close();
	}
	catch (BengineException& e)
	{
		std::cout << "caught: " << e.what()
			<< ": " << e.message() << std::endl;

		GTEST_FAIL();
	}
}

TEST(ObjFile, LoadFileWithOnlyVertices)
{
	try
	{
		ObjFile objFile;
		objFile.open(FileSystem::getInstance().path("./res/meshes/testCubeOnlyVertices.obj"));

		expect_objFile_eq_only_verts(objFile);

		objFile.close();
	}
	catch (BengineException& e)
	{
		std::cout << "caught: " << e.what()
			<< ": " << e.message() << std::endl;

		GTEST_FAIL();
	}
}

TEST(ObjFile, LoadFileWithQuadsAndOnlyVertices)
{
	try
	{
		ObjFile objFile;
		objFile.open(FileSystem::getInstance().path("./res/meshes/testCubeQuadsOnlyVertices.obj"));

		expect_objFile_eq_only_verts(objFile);

		objFile.close();
	}
	catch (BengineException& e)
	{
		std::cout << "caught: " << e.what()
			<< ": " << e.message() << std::endl;

		GTEST_FAIL();
	}
}