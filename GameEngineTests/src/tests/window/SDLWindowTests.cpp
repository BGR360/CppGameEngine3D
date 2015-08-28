#include <Testing.h>

#include <rendering/window/SDLWindow.h>

using Rendering::SDLWindow;

TEST(Window, SDLWindowConstructionDefault)
{
	SDLWindow sdlWindow;

	string name = sdlWindow.getName();
	int width = sdlWindow.getWidth();
	int height = sdlWindow.getHeight();

	string expectedName("SDL Window");
	int expectedWidth = 800;
	int expectedHeight = 600;

	EXPECT_EQ(expectedName, name);
	EXPECT_EQ(expectedWidth, width);
	EXPECT_EQ(expectedHeight, height);
}

TEST(Window, SDLWindowConstruction)
{
	SDLWindow sdlWindow("Hello World!", 400, 300);

	string name = sdlWindow.getName();
	int width = sdlWindow.getWidth();
	int height = sdlWindow.getHeight();

	string expectedName("Hello World!");
	int expectedWidth = 400;
	int expectedHeight = 300;

	EXPECT_EQ(expectedName, name);
	EXPECT_EQ(expectedWidth, width);
	EXPECT_EQ(expectedHeight, height);
}

TEST(Window, SDLWindowChangeName)
{
	SDLWindow sdlWindow;
	sdlWindow.setName("New Name");

	string name = sdlWindow.getName();
	int width = sdlWindow.getWidth();
	int height = sdlWindow.getHeight();

	string expectedName("New Name");
	int expectedWidth = 800;
	int expectedHeight = 600;

	EXPECT_EQ(expectedName, name);
	EXPECT_EQ(expectedWidth, width);
	EXPECT_EQ(expectedHeight, height);
}

TEST(Window, SDLWindowChangeWidth)
{
	SDLWindow sdlWindow;
	sdlWindow.setWidth(500);

	string name = sdlWindow.getName();
	int width = sdlWindow.getWidth();
	int height = sdlWindow.getHeight();

	string expectedName("SDL Window");
	int expectedWidth = 500;
	int expectedHeight = 600;

	EXPECT_EQ(expectedName, name);
	EXPECT_EQ(expectedWidth, width);
	EXPECT_EQ(expectedHeight, height);
}

TEST(Window, SDLWindowChangeHeight)
{
	SDLWindow sdlWindow;
	sdlWindow.setHeight(500);

	string name = sdlWindow.getName();
	int width = sdlWindow.getWidth();
	int height = sdlWindow.getHeight();

	string expectedName("SDL Window");
	int expectedWidth = 800;
	int expectedHeight = 500;

	EXPECT_EQ(expectedName, name);
	EXPECT_EQ(expectedWidth, width);
	EXPECT_EQ(expectedHeight, height);
}

#ifdef TEST_WINDOW_OPEN

TEST(Window, SDLWindowOpen)
{
	SDLWindow sdlWindow;
	sdlWindow.open();
	system("pause");
}

#endif //TEST_WINDOW_OPEN