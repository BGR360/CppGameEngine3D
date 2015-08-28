#include "Scene.h"

#include <iostream>

#include <qt/QtCore/qfile.h>
#include <qt/QtCore/qxmlstream.h>

#include <core/Game.h>
#include <rendering/RenderingEngine.h>
#include <rendering/ShaderProgram.h>

using std::cout;
using std::endl;

using Rendering::ShaderProgram;

namespace Core
{
	Scene::Scene() : m_rootObject(), m_resourceManager(), m_defaultCamera(new Camera), m_activeCamera(0) {}

	void Scene::initialize()
	{
		m_defaultCamera->setAspectRatio(getGame()->getRenderer()->getAspectRatio());

		if (m_activeCamera == 0)
		{
			m_activeCamera = m_defaultCamera;
		}

		this->start();
	}

	void Scene::start()
	{
		//Start the root object (the root object will start all of its children)
		this->getRoot()->start();
	}

	void Scene::update()
	{
		//cout << "Scene Update!" << endl;

		//Update the root object (the root object will update all of its children)
		this->getRoot()->update();

		//Update the view and projection matrices with the active camera
		ShaderProgram* currentShader = Rendering::getCurrentShader();
		if (currentShader != 0)
		{
			if (currentShader->hasUniform("viewMatrix"))
			{
				currentShader->setUniform("viewMatrix", m_activeCamera->toViewMatrix());
			}
			if (currentShader->hasUniform("projectionMatrix"))
			{
				currentShader->setUniform("projectionMatrix", m_activeCamera->toProjectionMatrix());
			}
			if (currentShader->hasUniform("viewProjectionMatrix"))
			{
				currentShader->setUniform("viewProjectionMatrix", m_activeCamera->toViewProjectionMatrix());
			}
		}
	}

	GameObject* Scene::getRoot()
	{
		return &m_rootObject;
	}

	void Scene::addGameObject(GameObject* gameObject)
	{
		m_rootObject.addChild(gameObject);
	}

	ResourceManager* Scene::getResourceManager()
	{
		return &m_resourceManager;
	}

	Camera* Scene::getActiveCamera()
	{
		return m_activeCamera;
	}

	Camera* Scene::getDefaultCamera()
	{
		return m_defaultCamera;
	}

	void Scene::setActiveCamera(Camera* camera)
	{
		m_activeCamera = camera;
	}

	void Scene::shutdown()
	{
		m_resourceManager.freeAllResources();
		delete m_defaultCamera;
	}

	Scene::~Scene()
	{
		this->shutdown();
	}
}