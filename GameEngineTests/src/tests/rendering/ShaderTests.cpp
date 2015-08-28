#include <Testing.h>

#include <iostream>

#include <exceptions/BengineException.h>
#include <exceptions/ShaderCompilingException.h>
#include <exceptions/ShaderLinkingException.h>
#include <rendering/RenderingEngine.h>
#include <rendering/ShaderProgram.h>
#include <util/filesys/FileSystem.h>

using Exceptions::BengineException;
using Exceptions::ShaderCompilingException;
using Exceptions::ShaderLinkingException;
using Rendering::RenderingEngine;
using Rendering::ShaderProgram;
using Rendering::IUniform;
using Rendering::UniformVariable;
using Util::FileSystem;

#ifdef RENDERING_TESTS

TEST(Shader, ConstructAndLoadValid)
{
	EXPECT_NO_THROW(ShaderProgram program(FileSystem::getInstance().path("./res/shaders/testShader")));

	try
	{
		ShaderProgram program2(FileSystem::getInstance().path("./res/shaders/testShader"));
	}
	catch (BengineException& e)
	{
		std::cout << "Caught: " << e.what() << ": " << e.message() << std::endl;
		GTEST_FAIL();
	}
}

TEST(Shader, CompilationFailure)
{
	EXPECT_THROW(ShaderProgram program(FileSystem::getInstance().path("./res/shaders/failShader")), ShaderCompilingException);

	try
	{
		ShaderProgram program2(FileSystem::getInstance().path("./res/shaders/failShader"));
	}
	catch (BengineException& e)
	{
		std::cout << "Caught: " << e.what() << ": " << e.message() << std::endl;
	}
}

TEST(Shader, NumUniforms)
{
	try
	{
		ShaderProgram program(FileSystem::getInstance().path("./res/shaders/uniformShader"));
		//program.addUniform<Vector3>("color");
		
		uint expectedNumUniforms = 4;
		uint numUniforms = program.getNumUniforms();

		EXPECT_EQ(expectedNumUniforms, numUniforms);
	}
	catch (BengineException& e)
	{
		std::cout << "Caught: " << e.what() << ": " << e.message() << std::endl;
		GTEST_FAIL();
	}
}

TEST(Shader, FindUniform)
{
	try
	{
		ShaderProgram program(FileSystem::getInstance().path("./res/shaders/uniformShader"));

		uint expectedIndex = 2;
		uint index = program.findUniform("translation");

		EXPECT_EQ(expectedIndex, index);
	}
	catch (BengineException& e)
	{
		std::cout << "Caught: " << e.what() << ": " << e.message() << std::endl;
		GTEST_FAIL();
	}
}

TEST(Shader, BindUniformLocation)
{
	try
	{
		ShaderProgram program(FileSystem::getInstance().path("./res/shaders/uniformShader"));
		//program.addUniform<Vector3>("color");

		IUniform* iuniform = program.getUniform("color");
		EXPECT_TRUE(iuniform != 0);

		if (iuniform != 0)
		{
			UniformVariable<Vector3>* uniform = dynamic_cast<UniformVariable<Vector3>*>(iuniform);
			EXPECT_TRUE(uniform != 0);

			if (uniform != 0)
			{
				GLuint expectedUniformLocation = glGetUniformLocation(program.getProgramID(), "color");
				GLuint uniformLocation = uniform->getLocation();

				EXPECT_TRUE(uniformLocation != -1);
				EXPECT_EQ(expectedUniformLocation, uniformLocation);
			}
		}
	}
	catch (BengineException& e)
	{
		std::cout << "Caught: " << e.what() << ": " << e.message() << std::endl;
		GTEST_FAIL();
	}
}

TEST(Shader, SetUniformData)
{
	try
	{
		ShaderProgram program(FileSystem::getInstance().path("./res/shaders/uniformShader"));
		//program.addUniform<Vector3>("color");

		Vector3 color(1, 1, 1);
		program.setUniform("color", color);

		IUniform* iuniform = program.getUniform("color");
		EXPECT_TRUE(iuniform != 0);

		if (iuniform != 0)
		{
			UniformVariable<Vector3>* uniform = dynamic_cast<UniformVariable<Vector3>*>(iuniform);
			EXPECT_TRUE(uniform != 0);

			if (uniform != 0)
			{
				Vector3 uniformData = uniform->getData();
				EXPECT_VEC3_EQ(color, uniformData);
			}
		}
	}
	catch (BengineException& e)
	{
		std::cout << "Caught: " << e.what() << ": " << e.message() << std::endl;
		GTEST_FAIL();
	}
}

TEST(Shader, HasUniform)
{
	try
	{
		ShaderProgram program(FileSystem::getInstance().path("./res/shaders/uniformShader"));

		EXPECT_TRUE(program.hasUniform("position"));
		EXPECT_TRUE(program.hasUniform("translation"));
		EXPECT_TRUE(program.hasUniform("xyScale"));
		EXPECT_TRUE(program.hasUniform("color"));
	}
	catch (BengineException& e)
	{
		std::cout << "Caught: " << e.what() << ": " << e.message() << std::endl;
		GTEST_FAIL();
	}
}

#endif //RENDERING_TESTS