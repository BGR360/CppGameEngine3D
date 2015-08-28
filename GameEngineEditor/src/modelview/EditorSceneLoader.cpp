#include "EditorSceneLoader.h"

#include <qt/QtCore/qdebug.h>

#include <modelview/GameObjectItem.h>
#include <modelview/EditorScene.h>
#include <EditorComponent.h>

Scene* EditorSceneLoader::generateScene()
{
	EditorScene* ret = new EditorScene;
	ret->getRoot()->addComponent(new EditorComponent);
	return ret;
}

GameObject* EditorSceneLoader::generateGameObject()
{
	return new GameObjectItem;
}

void EditorSceneLoader::loadGameObjectAttributes(GameObject* gameObject)
{
	SceneLoader::loadGameObjectAttributes(gameObject);

	GameObjectItem* item = dynamic_cast<GameObjectItem*>(gameObject);

	if (item != 0)
	{
		if (xml.attributes().hasAttribute("name"))
		{
			item->setName(xml.attributes().value("name").toString());
		}
	}
	else
	{
		qWarning() << "Wrong type of GameObject used in SceneGraphModel";
	}
}