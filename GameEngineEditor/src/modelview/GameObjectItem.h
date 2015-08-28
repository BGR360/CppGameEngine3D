#ifndef BENGINE_EDITOR_GAME_OBJECT_ITEM_H
#define BENGINE_EDITOR_GAME_OBJECT_ITEM_H

#include <qt/QtCore/qstring.h>

#include <core/GameObject.h>
using namespace Core;

class GameObjectItem : public GameObject
{
public:
	GameObjectItem() : m_name("GameObject") {}
	virtual ~GameObjectItem() {}

	QString getName() const { return m_name; }
	void setName(const QString& name) { m_name = name; }

	int row()
	{
		GameObjectItem* parent = static_cast<GameObjectItem*>(this->getTransform()->getParent()->getGameObject());
		if (parent != 0)
		{
			return parent->indexOf(this);
		}
		else
		{
			return 0;
		}
	}

private:
	QString m_name;

	int indexOf(GameObject* child)
	{
		for (uint i = 0; i < this->getNumChildren(); i++)
		{
			GameObject* comp = this->getChild(i);
			if (comp == child)
			{
				return (int)i;
			}
		}
		return -1;
	}
};

#endif //BENGINE_EDITOR_GAME_OBJECT_ITEM_H