#ifndef BENGINE_OPEN_GL_WINDOW_H
#define BENGINE_OPEN_GL_WINDOW_H

#include <Engine.h>

#include <rendering/window/Window.h>
#include <rendering/window/OpenGLWidget.h>

namespace Rendering
{
	class ENGINE_DLL_EXPORT_IMPORT OpenGLWindow : public Window
	{
		OpenGLWidget m_glWidget;

	public:
		OpenGLWindow();
		OpenGLWindow(string name, int width = 800, int height = 600);
		virtual ~OpenGLWindow();

		virtual void open();
		virtual void close();
		virtual void update();
	};
}

#endif //BENGINE_OPEN_GL_WINDOW_H