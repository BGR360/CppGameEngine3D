#include "OpenGLWidget.h"

#include <iostream>
#include <string>

#include <qt/QtGui/qopenglcontext.h>

#include <exceptions/OpenGLException.h>
#include <rendering/ShaderProgram.h>

using std::string;

using Exceptions::OpenGLException;

namespace Rendering
{
	OpenGLWidget::OpenGLWidget()
	{
		////Properly set up the QOpenGLContext

		//std::cout << "Creating OpenGL 3.3 context..." << std::endl;

		//QSurfaceFormat format;
		//// asks for a OpenGL 3.3 non-debug context using the Core profile
		//format.setMajorVersion(3);
		//format.setMinorVersion(3);
		//format.setProfile(QSurfaceFormat::CoreProfile);
		////format.setOption(QSurfaceFormat::DebugContext);

		//context()->setFormat(format);
		//if (!(context()->create()))
		//{
		//	throw OpenGLException("Failed to create OpenGL context.");
		//}

		//if (!(context()->isValid()))
		//{
		//	throw OpenGLException("Failed to create OpenGL context.");
		//}

		//context()->makeCurrent(context()->surface());

		//std::cout << "Success!" << std::endl;
	}

	void OpenGLWidget::initializeGL()
	{
		std::cout << "Initializing OpenGL..." << std::endl;

		//Use glew to initialize OpenGL

		std::cout << "Wrangling extensions..." << std::endl;

		glewExperimental = GL_TRUE;
		GLenum error = glewInit();

		if (error != GLEW_OK)
		{
			string message = "Failed to initialize OpenGL through glew: ";
			const unsigned char* errorMessage = glewGetErrorString(error);
			message += (const char*) errorMessage;
			throw OpenGLException(message);
		}

		std::cout << "Success!" << std::endl;

		std::cout << "Finished." << std::endl;
	}

	void OpenGLWidget::paintEvent()
	{
		//Leave blank so we can render when we want to
		std::cout << "paintEvent()" << std::endl;
	}

	//The real OpenGL magic must happen here
	void OpenGLWidget::paintGL()
	{
		
		std::cout << "paintGL()" << std::endl;
	}
}