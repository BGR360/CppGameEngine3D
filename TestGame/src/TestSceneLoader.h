#ifndef TESTGAME_TEST_SCENE_LOADER_H
#define TESTGAME_TEST_SCENE_LOADER_H

#include <util/SceneLoader.h>

#include "TestComponent.h"
#include "TestScene.h"

using Util::SceneLoader;

class TestSceneLoader : public SceneLoader
{
public:
	virtual Scene* generateScene()
	{
		cout << "Using a TestScene!" << endl;
		return new TestScene;
	}

	virtual void loadComponent(GameObject* gameObject, const string& componentType)
	{
		SceneLoader::loadComponent(gameObject, componentType);

		if (componentType.compare("TestComponent") == 0)
		{
			cout << "Creating a TestComponent!" << endl;
			gameObject->addComponent(new TestComponent);
		}
	}
};

#endif //TESTGAME_TEST_SCENE_LOADER_H