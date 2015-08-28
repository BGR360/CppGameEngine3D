#include "OpenGLWindow.h"

namespace Rendering
{
	OpenGLWindow::OpenGLWindow()
		: OpenGLWindow("OpenGL Window")
	{}

	OpenGLWindow::OpenGLWindow(string name, int width, int height)
		: Window(name, width, height), m_glWidget()
	{
		m_glWidget.setWindowTitle(name.c_str());
	}

	void OpenGLWindow::open()
	{
		m_glWidget.show();
	}

	void OpenGLWindow::close()
	{
		m_glWidget.hide();
	}

	void OpenGLWindow::update()
	{
		m_glWidget.resize(getWidth(), getHeight());
	}

	OpenGLWindow::~OpenGLWindow() {}
}