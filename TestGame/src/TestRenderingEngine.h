#ifndef TESTGAME_TEST_RENDERING_ENGINE_H
#define TESTGAME_TEST_RENDERING_ENGINE_H

#include <rendering/RenderingEngine.h>

using Rendering::RenderingEngine;

class TestRenderingEngine : public RenderingEngine
{
	bool isRed;

public:
	TestRenderingEngine() : isRed(true) {}

	void clearScreen()
	{
		isRed = !isRed;

		if (isRed)
		{
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		}

		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
};

#endif //TESTGAME_TEST_RENDERING_ENGINE_H