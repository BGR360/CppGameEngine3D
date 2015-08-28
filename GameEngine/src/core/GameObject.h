#ifndef BENGINE_GAMEOBJECT_H
#define BENGINE_GAMEOBJECT_H

#include <Engine.h>

#include <vector>

#include <core/Transform.h>
#include <util/Types.h>

using std::vector;

using Core::Transform;

namespace Core
{
	class ENGINE_DLL_EXPORT_IMPORT GameComponent;

	class ENGINE_DLL_EXPORT_IMPORT GameObject
	{
		uint m_id;
		Transform m_transform;

		vector<GameObject*> m_children;         //GameObject has ownership of its children
		vector<GameComponent*> m_components;    //GameObject has ownership of its GameComponents

	public:
		GameObject();
		virtual ~GameObject();

		void setID(uint id);
		void addComponent(GameComponent* component);
		void addChild(GameObject* child);
		void insertChild(GameObject* child, uint position);
		void removeChild(uint index);

		uint getID() const;

		uint getNumComponents() const;
		uint getNumChildren() const;

		template<class T>
		T* getComponent()
		{
			T* ret = 0;
			for (uint i = 0; i < m_components.size(); i++)
			{
				ret = dynamic_cast<T*>(m_components[i]);
				if (ret != 0)
					break;
			}

			return ret;
		}

		template<class T>
		void removeComponent()
		{
			T* comp = 0;
			for (uint i = 0; i < m_components.size(); i++)
			{
				comp = dynamic_cast<T*>(m_components[i]);
				if (ret != 0)
				{
					delete comp;
					m_components.erase(m_components.begin() + i);
					return;
				}
			}
		}

		GameObject* getChild(uint index);
		Transform* getTransform();

		//Do not override. Instead, make a custom GameComponent
		void start();
		void update();

	protected:
	private:
	};


	class GameComponent
	{
		GameObject* m_gameObject;

	public:
		GameComponent();
		virtual ~GameComponent();

		void attachToGameObject(GameObject* gameObject);
		GameObject* getGameObject() const;

		virtual void start();
		virtual void update();

	protected:
	private:
	};
}

#endif //BENGINE_GAMEOBJECT_H