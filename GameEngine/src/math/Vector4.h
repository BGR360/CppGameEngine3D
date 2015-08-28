#ifndef BENGINE_VECTOR4_H
#define BENGINE_VECTOR4_H

#include <Engine.h>

#include <math/Vector3.h>

using Math::Vector3;

namespace Math
{
	struct ENGINE_DLL_EXPORT Vector4
	{
		float x;
		float y;
		float z;
		float w;

		Vector4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
		Vector4(float x, float y, float z, float w = 1.0f) : x(x), y(y), z(z), w(w) {}
		Vector4(const Vector3& vec3, float w = 1.0f) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {}

		inline float magnitude() const;
		inline Vector4 normalized() const;
		inline Vector4 normalize();

		inline static float dot(const Vector4& left, const Vector4& right);
		inline static Vector4 normalize(Vector4& vec);
		inline static Vector4 normalize(const Vector4& vec);

		inline Vector4& operator+=(const Vector4& right);
		inline Vector4& operator-=(const Vector4& right);
		inline Vector4& operator*=(float scalar);
		inline Vector4& operator*=(const Vector4& right);
		inline Vector4& operator/=(float scalar);
		inline Vector4& operator/=(const Vector4& right);

		inline float& operator[] (const int nIndex);
	};

	inline Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
	inline Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
	inline Vector4 operator*(float scalar, const Vector4& vector);
	inline Vector4 operator*(const Vector4& vector, float scalar);
	inline Vector4 operator*(const Vector4& lhs, const Vector4& rhs);
	inline Vector4 operator/(const Vector4& vector, float scalar);
	inline Vector4 operator/(const Vector4& lhs, const Vector4& rhs);

#include "Vector4.inl"
}

#endif //BENGINE_VECTOR4_H