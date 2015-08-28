#ifndef BENGINE_MATRIX_2X2_H
#define BENGINE_MATRIX_2X2_H

#include <Engine.h>

#include <math/Math.h>
#include <math/Vector2.h>

using Math::toRadians;
using Math::Vector2;

//All Matrices will be stored in column-major order to reflect OpenGL matrix storage

namespace Math
{
	struct ENGINE_DLL_EXPORT Matrix2x2
	{
		float c0r0, c0r1;
		float c1r0, c1r1;

		Matrix2x2(
			float r0c0 = 1.0f, float r0c1 = 0.0f,
			float r1c0 = 0.0f, float r1c1 = 1.0f)
			:
			c0r0(r0c0), c0r1(r1c0),
			c1r0(r0c1), c1r1(r1c1) 
		{}

		//Classic Matrix operations
		inline static Matrix2x2 adjugate(const Matrix2x2& matrix);
		inline static float determinant(const Matrix2x2& matrix);
		inline static Matrix2x2 inverse(const Matrix2x2& matrix);
		inline static Matrix2x2 transpose(const Matrix2x2& matrix);

		//Game-related Matrix operations
		inline static Matrix2x2 scale(const Vector2& scale);
		inline static Matrix2x2 rotate(float thetaDegrees);
	};

	inline Matrix2x2 operator+(const Matrix2x2& left, const Matrix2x2& right);
	inline Matrix2x2 operator-(const Matrix2x2& left, const Matrix2x2& right);
	inline Vector2 operator*(const Matrix2x2& op, const Vector2& vec);
	inline Matrix2x2 operator*(float op, const Matrix2x2& matrix);
	inline Matrix2x2 operator*(const Matrix2x2& left, const Matrix2x2& right);

	#include "Matrix2x2.inl"
}

#endif //BENGINE_MATRIX_2X2_H