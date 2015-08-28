#ifndef TESTGAME_POSITION_COMPONENT_H
#define TESTGAME_POSITION_COMPONENT_H

#include <core/GameObject.h>
using namespace Core;

class PositionComponent : public GameComponent
{
	Vector3 m_startPos;

public:
	PositionComponent(const Vector3& startPos) : m_startPos(startPos) {}

	virtual void start()
	{
		getGameObject()->getTransform()->setPosition(m_startPos);
	}

	virtual void update()
	{

	}
};

#endif //TESTGAME_POSITION_COMPONENT_H