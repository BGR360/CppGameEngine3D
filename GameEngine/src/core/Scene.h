#ifndef BENGINE_SCENE_H
#define BENGINE_SCENE_H

#include <Engine.h>

#include <core/GameObject.h>
#include <rendering/Camera.h>
#include <resources/ResourceManager.h>

namespace Rendering
{
	class RenderingEngine;
}

using Rendering::Camera;
using Rendering::RenderingEngine;
using Resources::ResourceManager;

namespace Core
{
	class Game;

	class ENGINE_DLL_EXPORT_IMPORT Scene
	{
		GameObject m_rootObject;
		ResourceManager m_resourceManager;
		Camera* m_defaultCamera;
		Camera* m_activeCamera;

	public:
		Scene();
		virtual ~Scene();

		void initialize();
		void shutdown();

		virtual void update();	//TODO make this non-virtual. Have everything done in custom GameComponents

		//Don't override
		void start();

		void addGameObject(GameObject* gameObject);
		
		virtual GameObject* getRoot();
		ResourceManager* getResourceManager();

		Camera* getActiveCamera();
		Camera* getDefaultCamera();
		void setActiveCamera(Camera* camera);
	};
}

#endif //BENGINE_SCENE_H