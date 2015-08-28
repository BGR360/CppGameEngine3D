#ifndef BENGINE_CAMERA_H
#define BENGINE_CAMERA_H

#include <Engine.h>

#include <math/Vector3.h>
#include <math/Matrix4x4.h>

using Math::Vector3;
using Math::Matrix4x4;

namespace Rendering
{
	class ENGINE_DLL_EXPORT Camera
	{
		Vector3 m_position;
		Vector3 m_forward;
		Vector3 m_up;
		float m_fov;
		float m_aspectRatio;
		float m_zNear;
		float m_zFar;

	public:
		Camera() :
			m_fov(120.0f), m_aspectRatio(1.0f), 
			m_zNear(0.1f), m_zFar(100.0f),
			m_position(0.0f, 0.0f, 0.0f),
			m_forward(0.0f, 0.0f, -1.0f),
			m_up(0.0f, 1.0f, 0.0f)
		{}
		virtual ~Camera() {}

		inline Vector3 getPosition() const;
		inline Vector3& getPosition();

		inline Vector3 getForward() const;
		inline Vector3& getForward();

		inline Vector3 getUp() const;
		inline Vector3& getUp();

		inline float getFov() const;
		inline float& getFov();

		inline float getAspectRatio() const;
		inline float& getAspectRatio();

		inline float getNear() const;
		inline float& getNear();

		inline float getFar() const;
		inline float& getFar();

		inline Vector3 getTarget() const;
		inline Vector3 getRight() const;

		inline void setPosition(const Vector3& pos);
		inline void setTarget(const Vector3& target);
		inline void setViewDirection(const Vector3& direction);
		inline void setUp(const Vector3& up);
		inline void setFov(float fov);
		inline void setAspectRatio(float aspectRatio);
		inline void setNear(float near);
		inline void setFar(float far);

		inline void rotateX(float angle);
		inline void rotateY(float angle);

		inline Matrix4x4 toViewMatrix() const;
		inline Matrix4x4 toProjectionMatrix() const;
		inline Matrix4x4 toViewProjectionMatrix() const;
	};

	#include "Camera.inl"
}

#endif //BENGINE_CAMERA_H