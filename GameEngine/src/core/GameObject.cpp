#include "GameObject.h"

#include <exceptions/BengineException.h>

using Exceptions::BengineException;

namespace Core
{
	GameObject::GameObject()
		: m_transform(),
		m_id(0)
	{
		m_children = vector<GameObject*>();
		m_components = vector<GameComponent*>();
		m_transform.attachToGameObject(this);
	}

	void GameObject::setID(uint id)
	{
		m_id = id;
	}

	void GameObject::addComponent(GameComponent* component)
	{
		m_components.push_back(component);
		component->attachToGameObject(this);
	}

	void GameObject::addChild(GameObject* child)
	{
		m_children.push_back(child);
		Transform* childTransform = child->getTransform();
		childTransform->setParent(&m_transform);
	}

	void GameObject::insertChild(GameObject* child, uint position)
	{		
		if (position < 0 || position > m_children.size())
		{
			throw BengineException("Array Index Out of Bounds: cannot insert at this location.");
		}

		m_children.insert(m_children.begin() + position, child);
		Transform* childTransform = child->getTransform();
		childTransform->setParent(&m_transform);
	}

	void GameObject::removeChild(uint index)
	{
		if (index >= 0 && index < m_children.size())
		{
			GameObject* child = m_children[index];
			delete child;
			m_children.erase(m_children.begin() + index);
		}
	}

	uint GameObject::getID() const
	{
		return m_id;
	}

	uint GameObject::getNumComponents() const
	{
		return m_components.size();
	}

	uint GameObject::getNumChildren() const
	{
		return m_children.size();
	}

	GameObject* GameObject::getChild(uint index)
	{
		return m_children[index];
	}

	Transform* GameObject::getTransform()
	{
		return &m_transform;
	}

	void GameObject::start()
	{
		//Start all of my GameComponents
		vector<GameComponent*>::iterator comp;
		for (comp = m_components.begin(); comp != m_components.end(); comp++)
		{
			(*comp)->start();
		}

		//Start all of my children
		vector<GameObject*>::iterator child;
		for (child = m_children.begin(); child != m_children.end(); child++)
		{
			(*child)->start();
		}
	}

	void GameObject::update()
	{
		//Update all of my GameComponents
		vector<GameComponent*>::iterator comp;
		for (comp = m_components.begin(); comp != m_components.end(); comp++)
		{
			(*comp)->update();
		}

		//Update all of my children
		vector<GameObject*>::iterator child;
		for (child = m_children.begin(); child != m_children.end(); child++)
		{
			(*child)->update();
		}
	}

	GameObject::~GameObject()
	{
		//Must delete all GameComponents
		for (uint i = 0; i < m_components.size(); i++)
		{
			if (m_components[i] != 0)
			{
				delete m_components[i];
			}
		}
		m_components.clear();

		//Must delete all children GameObjects
		for (uint i = 0; i < m_children.size(); i++)
		{
			if (m_children[i] != 0)
			{
				delete m_children[i];
			}
		}
		m_children.clear();
	}



	GameComponent::GameComponent() : m_gameObject(0) {}

	void GameComponent::attachToGameObject(GameObject* gameObject)
	{
		m_gameObject = gameObject;
	}

	GameObject* GameComponent::getGameObject() const
	{
		return m_gameObject;
	}

	void GameComponent::start() {}
	void GameComponent::update() {}

	GameComponent::~GameComponent() {}
}