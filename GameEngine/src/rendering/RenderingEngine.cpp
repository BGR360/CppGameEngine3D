#include "RenderingEngine.h"

#include <iostream>

#include <qt/QtGui/qopenglcontext.h>

#include <core/Game.h>
#include <core/Scene.h>
#include <core/component/RenderingComponent.h>
#include <exceptions/OpenGLException.h>

using std::cout;
using std::endl;

using Core::getGame;
using Core::Scene;
using Core::Component::RenderingComponent;
using Exceptions::OpenGLException;

namespace Rendering
{
	RenderingEngine::RenderingEngine(QWidget* parent)
		: QOpenGLWidget(parent),
		m_activeScene(0)
	{}

	void RenderingEngine::initialize()
	{
		this->show();
	}

	float RenderingEngine::getAspectRatio() const
	{
		return (float)width() / height();
	}

	void RenderingEngine::initializeGL()
	{
		cout << "Initializing OpenGL..." << endl;

		//Use glew to initialize OpenGL

		cout << "Wrangling extensions..." << endl;

		glewExperimental = GL_TRUE;
		GLenum error = glewInit();

		if (error != GLEW_OK)
		{
			string message = "Failed to initialize OpenGL through glew: ";
			const unsigned char* errorMessage = glewGetErrorString(error);
			message += (const char*)errorMessage;
			throw OpenGLException(message);
		}

		cout << "Success!" << endl;

		glEnable(GL_DEPTH_TEST);

		cout << "Finished." << endl;
	}

	void RenderingEngine::paintEvent()
	{
		//Leave blank so we can render when we want to
		cout << "paintEvent()" << endl;
	}

	void RenderingEngine::renderScene(Scene* scene)
	{
		m_activeScene = scene;
		repaint();
	}

	void RenderingEngine::paintGL()
	{
		//cout << "paintGL()" << endl;

		//First we must clear the color and depth buffers
		this->clearBuffers();

		//Then we can render the scene
		if (m_activeScene != 0)
		{
			//Update camera's aspectRatio
			m_activeScene->getActiveCamera()->setAspectRatio(this->getAspectRatio());

			//Render the root object of our active scene
			this->renderGameObject(m_activeScene->getRoot());
		}
		else
		{
			this->clearBuffers();
		}
	}

	void RenderingEngine::wheelEvent(QWheelEvent* e)
	{
		getGame()->getInput()->wheelEvent(e);
	}

	void RenderingEngine::clearBuffers()
	{
		glClearColor(0, 0, 0, 1);
		glClearDepth(1);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderingEngine::renderGameObject(GameObject* gameObject)
	{
		//Get a RenderingComponent from gameObject and invoke render() on it
		RenderingComponent* rc = gameObject->getComponent<RenderingComponent>();

		if (rc != 0)
		{
			rc->render();
		}

		//For all of gameObject's children, call render() on them
		uint numChildren = gameObject->getNumChildren();
		for (uint i = 0; i < numChildren; i++)
		{
			this->renderGameObject(gameObject->getChild(i));
		}
	}

	void RenderingEngine::shutdown()
	{
		this->hide();
	}

	RenderingEngine::~RenderingEngine() 
	{
		this->shutdown();
	}
}