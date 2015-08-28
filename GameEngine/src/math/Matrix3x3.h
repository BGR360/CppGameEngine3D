#ifndef BENGINE_MATRIX_3X3_H
#define BENGINE_MATRIX_3X3_H

#include <Engine.h>

#include <math/Matrix2x2.h>
#include <math/Vector3.h>

using Math::Matrix2x2;
using Math::Vector3;

//All Matrices will be stored in column-major order to reflect OpenGL matrix storage

namespace Math
{
	struct ENGINE_DLL_EXPORT Matrix3x3
	{
		float c0r0, c0r1, c0r2;
		float c1r0, c1r1, c1r2;
		float c2r0, c2r1, c2r2;

		Matrix3x3(
			float r0c0 = 1.0f, float r0c1 = 0.0f, float r0c2 = 0.0f,
			float r1c0 = 0.0f, float r1c1 = 1.0f, float r1c2 = 0.0f,
			float r2c0 = 0.0f, float r2c1 = 0.0f, float r2c2 = 1.0f)
			:
			c0r0(r0c0), c0r1(r1c0), c0r2(r2c0),
			c1r0(r0c1), c1r1(r1c1), c1r2(r2c1),
			c2r0(r0c2), c2r1(r1c2), c2r2(r2c2)
		{}

		Matrix3x3(const Matrix2x2& mat2,		  float r0c2 = 0.0f,
												  float r1c2 = 0.0f,
			float r2c0 = 0.0f, float r2c1 = 0.0f, float r2c2 = 1.0f)
			:
			c0r0(mat2.c0r0), c0r1(mat2.c0r1), c0r2(r2c0),
			c1r0(mat2.c1r0), c1r1(mat2.c1r1), c1r2(r2c1),
			c2r0(r0c2),		 c2r1(r1c2),	  c2r2(r2c2)
		{}

		inline Matrix2x2 getMatrix2x2();

		//Classic Matrix operations
		inline static Matrix3x3 adjugate(const Matrix3x3& matrix);
		inline static Matrix3x3 cofactor(const Matrix3x3& matrix);
		inline static float determinant(const Matrix3x3& matrix);
		inline static Matrix3x3 inverse(const Matrix3x3& matrix);
		inline static Matrix3x3 tilde(const Vector3& vec);
		inline static Matrix3x3 transpose(const Matrix3x3& matrix);

		//Game-related Matrix operations
		inline static Matrix3x3 scale(const Vector3& scale);
		inline static Matrix3x3 rotate(float angleDegrees, const Vector3& axis);
		inline static Matrix3x3 rotate(const Vector3& eulerAngles);
		inline static Matrix3x3 rotate(float degreesX, float degreesY, float degreesZ);
		inline static Matrix3x3 translate(const Vector2& translation);
		inline static Matrix3x3 translate(const Vector3& translation);

		inline static Matrix3x3 lookAt(
			const Vector3& position,
			const Vector3& target,
			const Vector3& up = Vector3(0, 1.0f, 0));
	};

	inline Matrix3x3 operator+(const Matrix3x3& left, const Matrix3x3& right);
	inline Matrix3x3 operator-(const Matrix3x3& left, const Matrix3x3& right);
	inline Vector3 operator*(const Matrix3x3& op, const Vector3& vec);
	inline Matrix3x3 operator*(float op, const Matrix3x3& matrix);
	inline Matrix3x3 operator*(const Matrix3x3& left, const Matrix3x3& right);

#include "Matrix3x3.inl"
}

#endif //BENGINE_MATRIX_3X3_H