#ifndef BENGINE_EDITOR_EDITOR_SCENE_LOADER_H
#define BENGINE_EDITOR_EDITOR_SCENE_LOADER_H

#include <util/SceneLoader.h>
using namespace Util;

class EditorSceneLoader : public SceneLoader
{
public:
	EditorSceneLoader(const string& filePath = "") : SceneLoader(filePath) {}
	virtual ~EditorSceneLoader() {}
protected:
	virtual Scene* generateScene();
	virtual GameObject* generateGameObject();
	virtual void loadGameObjectAttributes(GameObject* gameObject);
};

#endif //BENGINE_EDITOR_EDITOR_SCENE_LOADER_H