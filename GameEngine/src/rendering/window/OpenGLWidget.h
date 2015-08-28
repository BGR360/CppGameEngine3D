#ifndef BENGINE_OPEN_GL_WIDGET_H
#define BENGINE_OPEN_GL_WIDGET_H

#include <rendering/OpenGL.h>

#include <qt/QtWidgets/qopenglwidget.h>

namespace Rendering
{
	class OpenGLWidget : public QOpenGLWidget
	{
	public:
		OpenGLWidget();
		void swapBuffers();

	protected:
		void initializeGL();

		//@Override
		void paintEvent();
		//@Override
		void paintGL();
	};
}

#endif //BENGINE_OPEN_GL_WIDGET_H