#include <Testing.h>

#include <rendering/ShaderProgram.h>
#include <resources/Image.h>
#include <resources/ResourceManager.h>

using Resources::Image;
using Resources::Image;
using Resources::ResourceManager;
using Rendering::ShaderProgram;

TEST(ResourceManager, LoadAndGetImage)
{
	ResourceManager resourceManager;

	Image* loadedImage = resourceManager.loadImage("./res/images/bricks.jpg");
	Image* gottenImage = resourceManager.getImage("bricks.jpg");

	EXPECT_EQ(loadedImage, gottenImage);

	EXPECT_TRUE(loadedImage->format() == QImage::Format_RGB888 || loadedImage->format() == QImage::Format_RGBA8888);
}

#ifdef RENDERING_TESTS

TEST(ResourceManager, LoadAndGetShader)
{
	ResourceManager resourceManager;

	ShaderProgram* loadedShader = resourceManager.loadShader("./res/shaders/testShader");
	ShaderProgram* gottenShader = resourceManager.getShader("testShader");

	EXPECT_EQ(loadedShader, gottenShader);
}

TEST(ResourceManager, LoadShaderWithFileExtension)
{
	ResourceManager resourceManager;

	ShaderProgram* loadedShader = resourceManager.loadShader("./res/shaders/testShader.shader");
	ShaderProgram* gottenShader = resourceManager.getShader("testShader");

	EXPECT_EQ(loadedShader, gottenShader);
}

#endif //RENDERING_TESTS