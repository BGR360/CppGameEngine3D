#ifndef BENGINE_VECTOR2_H
#define BENGINE_VECTOR2_H

#include <cassert>

#include <Engine.h>

extern float sqrt(float val);

namespace Math
{
	struct ENGINE_DLL_EXPORT_IMPORT Vector2
	{
		float x;
		float y;

		Vector2() : x(0.0f), y(0.0f) {}
		Vector2(float x, float y) : x(x), y(y) {}

		inline float magnitude() const;
		inline Vector2 normalized() const;
		inline Vector2 normalize();

		inline static float dot(const Vector2& left, const Vector2& right);
		inline static Vector2 normalize(Vector2& vec);
		inline static Vector2 normalize(const Vector2& vec);

		inline Vector2& operator+=(const Vector2& right);
		inline Vector2& operator-=(const Vector2& right);
		inline Vector2& operator*=(float scalar);
		inline Vector2& operator*=(const Vector2& right);
		inline Vector2& operator/=(float scalar);
		inline Vector2& operator/=(const Vector2& right);

		inline float& operator[] (const int nIndex);
	};

	inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
	inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
	inline Vector2 operator*(float scalar, const Vector2& vector);
	inline Vector2 operator*(const Vector2& vector, float scalar);
	inline Vector2 operator*(const Vector2& lhs, const Vector2& rhs);
	inline Vector2 operator/(const Vector2& vector, float scalar);
	inline Vector2 operator/(const Vector2& lhs, const Vector2& rhs);

#include "Vector2.inl"
}

#endif //BENGINE_VECTOR2_H