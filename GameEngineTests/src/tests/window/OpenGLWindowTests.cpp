#include <Testing.h>

#include <rendering/window/OpenGLWindow.h>

using Rendering::OpenGLWindow;

TEST(Window, OpenGLWindowConstructionDefault)
{
	OpenGLWindow glWindow;

	string name = glWindow.getName();
	int width = glWindow.getWidth();
	int height = glWindow.getHeight();

	string expectedName("OpenGL Window");
	int expectedWidth = 800;
	int expectedHeight = 600;

	EXPECT_EQ(expectedName, name);
	EXPECT_EQ(expectedWidth, width);
	EXPECT_EQ(expectedHeight, height);
}

TEST(Window, OpenGLWindowConstruction)
{
	OpenGLWindow glWindow("Hello World!", 400, 300);

	string name = glWindow.getName();
	int width = glWindow.getWidth();
	int height = glWindow.getHeight();

	string expectedName("Hello World!");
	int expectedWidth = 400;
	int expectedHeight = 300;

	EXPECT_EQ(expectedName, name);
	EXPECT_EQ(expectedWidth, width);
	EXPECT_EQ(expectedHeight, height);
}

TEST(Window, OpenGLWindowChangeName)
{
	OpenGLWindow glWindow;
	glWindow.setName("New Name");

	string name = glWindow.getName();
	int width = glWindow.getWidth();
	int height = glWindow.getHeight();

	string expectedName("New Name");
	int expectedWidth = 800;
	int expectedHeight = 600;

	EXPECT_EQ(expectedName, name);
	EXPECT_EQ(expectedWidth, width);
	EXPECT_EQ(expectedHeight, height);
}

TEST(Window, OpenGLWindowChangeWidth)
{
	OpenGLWindow glWindow;
	glWindow.setWidth(500);

	string name = glWindow.getName();
	int width = glWindow.getWidth();
	int height = glWindow.getHeight();

	string expectedName("OpenGL Window");
	int expectedWidth = 500;
	int expectedHeight = 600;

	EXPECT_EQ(expectedName, name);
	EXPECT_EQ(expectedWidth, width);
	EXPECT_EQ(expectedHeight, height);
}

TEST(Window, OpenGLWindowChangeHeight)
{
	OpenGLWindow glWindow;
	glWindow.setHeight(500);

	string name = glWindow.getName();
	int width = glWindow.getWidth();
	int height = glWindow.getHeight();

	string expectedName("OpenGL Window");
	int expectedWidth = 800;
	int expectedHeight = 500;

	EXPECT_EQ(expectedName, name);
	EXPECT_EQ(expectedWidth, width);
	EXPECT_EQ(expectedHeight, height);
}

#ifdef TEST_WINDOW_OPEN

TEST(Window, OpenGLWindowOpen)
{
	OpenGLWindow glWindow;
	glWindow.open();
	system("pause");
	glWindow.close();
}

#endif //TEST_WINDOW_OPEN