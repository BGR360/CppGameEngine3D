#ifndef BENGINE_EDITOR_EDITOR_SCENE_H
#define BENGINE_EDITOR_EDITOR_SCENE_H

#include <core/Scene.h>
using namespace Core;

#include <modelview/GameObjectItem.h>

class EditorScene : public Scene
{
public:
	EditorScene() {}
	virtual ~EditorScene() {}

	virtual GameObject* getRoot()
	{
		return &m_root;
	}

private:
	GameObjectItem m_root;
};

#endif //BENGINE_EDITOR_EDITOR_SCENE_H