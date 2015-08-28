#ifndef BENGINE_TRANSFORM_H
#define BENGINE_TRANSFORM_H

#include <Engine.h>

#include <math/Matrix4x4.h>
#include <math/Vector3.h>

using Math::Matrix4x4;
using Math::Vector3;

namespace Core
{
	class GameObject;

	class ENGINE_DLL_EXPORT Transform
	{
		Vector3 m_position;
		Vector3 m_rotation;
		Vector3 m_scale;

		Transform* m_parent;
		GameObject* m_gameObject;

	public:
		Transform()
			:m_position(0.0f, 0.0f, 0.0f),
			m_rotation(0.0f, 0.0f, 0.0f),
			m_scale(1.0f, 1.0f, 1.0f),
			m_parent()
		{}
		Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale)
			:m_position(position),
			m_rotation(rotation),
			m_scale(scale),
			m_parent(0)
		{}
		virtual ~Transform() {}

		inline Vector3& getPosition();
		inline Vector3& getRotation();
		inline Vector3& getScale();

		inline Vector3 getPosition() const;
		inline Vector3 getRotation() const;
		inline Vector3 getScale() const;
		inline Transform* getParent() const;
		inline GameObject* getGameObject() const;

		inline Matrix4x4 toModelMatrix() const;

		inline void setPosition(const Vector3& position);
		inline void setRotation(const Vector3& rotation);
		inline void setScale(const Vector3& scale);

		inline void setParent(Transform* parent);
		inline void clearParent();

		inline void attachToGameObject(GameObject* gameObject);

	protected:
	private:
	};

#include "Transform.inl" 
}

#endif //BENGINE_TRANSFORM_H