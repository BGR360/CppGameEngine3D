#ifndef BENGINE_MATRIX_4X4_H
#define BENGINE_MATRIX_4X4_H

#include <Engine.h>

#include <math/Matrix3x3.h>
#include <math/Vector4.h>

using Math::Matrix3x3;
using Math::Vector4;

//All Matrices will be stored in column-major order to reflect OpenGL matrix storage

namespace Math
{
	struct ENGINE_DLL_EXPORT Matrix4x4
	{
		float c0r0, c0r1, c0r2, c0r3;
		float c1r0, c1r1, c1r2, c1r3;
		float c2r0, c2r1, c2r2, c2r3;
		float c3r0, c3r1, c3r2, c3r3;

		Matrix4x4(
			float r0c0 = 1.0f, float r0c1 = 0.0f, float r0c2 = 0.0f, float r0c3 = 0.0f,
			float r1c0 = 0.0f, float r1c1 = 1.0f, float r1c2 = 0.0f, float r1c3 = 0.0f,
			float r2c0 = 0.0f, float r2c1 = 0.0f, float r2c2 = 1.0f, float r2c3 = 0.0f,
			float r3c0 = 0.0f, float r3c1 = 0.0f, float r3c2 = 0.0f, float r3c3 = 1.0f)
			:
			c0r0(r0c0), c0r1(r1c0), c0r2(r2c0), c0r3(r3c0),
			c1r0(r0c1), c1r1(r1c1), c1r2(r2c1), c1r3(r3c1),
			c2r0(r0c2), c2r1(r1c2), c2r2(r2c2), c2r3(r3c2),
			c3r0(r0c3), c3r1(r1c3), c3r2(r2c3), c3r3(r3c3)
		{}

		Matrix4x4(const Matrix3x3& mat3,							 float r0c3 = 0.0f,
																	 float r1c3 = 0.0f,
																	 float r2c3 = 0.0f,
			float r3c0 = 0.0f, float r3c1 = 0.0f, float r3c2 = 0.0f, float r3c3 = 1.0f)
			:
			c0r0(mat3.c0r0), c0r1(mat3.c0r1), c0r2(mat3.c0r2), c0r3(r3c0),
			c1r0(mat3.c1r0), c1r1(mat3.c1r1), c1r2(mat3.c1r2), c1r3(r3c1),
			c2r0(mat3.c2r0), c2r1(mat3.c2r1), c2r2(mat3.c2r2), c2r3(r3c2),
			c3r0(r0c3),		 c3r1(r1c3),	  c3r2(r2c3),	   c3r3(r3c3)
		{}

		inline Matrix3x3 getMatrix3x3();

		//Game-related Matrix operations
		inline static Matrix4x4 scale(const Vector3& scale);
		inline static Matrix4x4 rotate(const Vector3& eulerAngles);
		inline static Matrix4x4 rotate(float degreesX, float degreesY, float degreesZ);
		inline static Matrix4x4 translate(const Vector3& translation);
		inline static Matrix4x4 translate(const Vector4& translation);

		inline static Matrix4x4 lookAt(
			const Vector3& position, 
			const Vector3& target, 
			const Vector3& up = Vector3(0, 1.0f, 0));

		inline static Matrix4x4 perspective(float fov, float aspectRatio, float zNear, float zFar);
	};

	inline Matrix4x4 operator+(const Matrix4x4& left, const Matrix4x4& right);
	inline Matrix4x4 operator-(const Matrix4x4& left, const Matrix4x4& right);
	inline Vector4 operator*(const Matrix4x4& op, const Vector4& vec);
	inline Matrix4x4 operator*(float op, const Matrix4x4& matrix);
	inline Matrix4x4 operator*(const Matrix4x4& left, const Matrix4x4& right);

#include "Matrix4x4.inl"
}

#endif //BENGINE_MATRIX_4X4_H