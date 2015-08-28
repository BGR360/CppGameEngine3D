#ifndef BENGINE_SCENE_LOADER_H
#define BENGINE_SCENE_LOADER_H

#include <Engine.h>

#include <string>

#include <qt/QtCore/qfile.h>
#include <qt/QtCore/qxmlstream.h>

#include <core/Scene.h>
#include <math/Vector3.h>

using std::string;

using Core::Scene;
using Core::GameComponent;
using Core::GameObject;
using Math::Vector3;
using Resources::ResourceManager;

namespace Util
{
	class ENGINE_DLL_EXPORT_IMPORT SceneLoader
	{
		string m_filePath;
		QStringRef qname;
		string name;
		string text;
		bool isStart;
		bool isEnd;

	protected:
		QXmlStreamReader xml;
		Scene* m_scene;

	public:
		SceneLoader(const string& filePath = "") : m_filePath(filePath), m_scene(0) {}
		virtual ~SceneLoader() {}
		void loadFromXml();
		void loadFromXml(const string& filePath);
		Scene* getScene();

	protected:
		virtual Scene* generateScene();
		virtual GameObject* generateGameObject();
		virtual GameObject* loadGameObjectFromXml(GameObject* parent);
		virtual void loadGameObjectAttributes(GameObject* gameObject);
		virtual void loadComponent(GameObject* gameObject, const string& componentType);

		void loadResourcesFromXml();
		void loadShaders(ResourceManager* res);
		void loadMeshes(ResourceManager* res);
		void loadImages(ResourceManager* res);
		void loadTextures(ResourceManager* res);
		void loadMaterials(ResourceManager* res);
		void loadCameraFromXml();
		void createObjectTreeFromXml();
		void loadTransformForObject(GameObject* gameObject);
		void loadComponentsForObject(GameObject* gameObject);
		Vector3 loadVector3FromXml();

	private:
		void update();
	};
}

#endif //BENGINE_SCENE_LOADER_H