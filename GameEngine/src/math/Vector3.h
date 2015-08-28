#ifndef BENGINE_VECTOR3_H
#define BENGINE_VECTOR3_H

#include <Engine.h>

#include <math/Vector2.h>

using Math::Vector2;

namespace Math
{
	struct ENGINE_DLL_EXPORT_IMPORT Vector3
	{
		float x;
		float y;
		float z;

		Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vector3(float x, float y, float z = 1.0f) : x(x), y(y), z(z) {}
		Vector3(const Vector2& vec2, float z = 1.0f) : x(vec2.x), y(vec2.y), z(z) {}

		inline float magnitude() const;
		inline Vector3 normalized() const;
		inline Vector3 normalize();

		inline static float dot(const Vector3& left, const Vector3& right);
		inline static Vector3 cross(const Vector3& left, const Vector3& right);
		inline static Vector3 normalize(Vector3& vec);
		inline static Vector3 normalize(const Vector3& vec);

		inline Vector3& operator+=(const Vector3& right);
		inline Vector3& operator-=(const Vector3& right);
		inline Vector3& operator*=(float scalar);
		inline Vector3& operator*=(const Vector3& right);
		inline Vector3& operator/=(float scalar);
		inline Vector3& operator/=(const Vector3& right);

		inline float& operator[] (const int nIndex);
	};

	inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
	inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
	inline Vector3 operator*(float scalar, const Vector3& vector);
	inline Vector3 operator*(const Vector3& vector, float scalar);
	inline Vector3 operator*(const Vector3& lhs, const Vector3& rhs);
	inline Vector3 operator/(const Vector3& vector, float scalar);
	inline Vector3 operator/(const Vector3& lhs, const Vector3& rhs);

	#include "Vector3.inl"
}

#endif //BENGINE_VECTOR3_H