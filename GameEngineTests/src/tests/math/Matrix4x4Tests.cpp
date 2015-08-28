#include <Testing.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <math/Matrix4x4.h>
#include <math/Vector4.h>

using Math::Matrix4x4;
using Math::Vector4;

void vec3ToVector3(const glm::vec3& vec3, Vector3& vector3);
void mat4ToMatrix4x4(const glm::mat4& mat4, Matrix4x4& mat4x4);

#ifdef MATH_TESTS

TEST(Matrix4x4, Identity)
{
	Matrix4x4 identity;

	Matrix4x4 expected(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	EXPECT_MAT4_EQ(expected, identity);
}

TEST(Matrix4x4, ConstructFrom3x3)
{
	Matrix3x3 matrix3x3(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Matrix4x4 matrix(matrix3x3);
	Matrix4x4 expected(
		1, 2, 3, 0,
		4, 5, 6, 0,
		7, 8, 9, 0,
		0, 0, 0, 1);

	EXPECT_MAT4_EQ(expected, matrix);
}

TEST(Matrix4x4, Addition)
{
	Matrix4x4 left(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);
	Matrix4x4 right(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);
	Matrix4x4 expected(
		2, 4, 6, 8,
		10, 12, 14, 16,
		18, 20, 22, 24,
		26, 28, 30, 32);

	Matrix4x4 result = left + right;
	EXPECT_MAT4_EQ(expected, result);
}

TEST(Matrix4x4, Subtraction)
{
	Matrix4x4 left(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);
	Matrix4x4 right(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);
	Matrix4x4 expected(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);

	Matrix4x4 result = left - right;
	EXPECT_MAT3_EQ(expected, result);
}

TEST(Matrix4x4, ScalarMultiplication)
{
	float op = 2.0f;
	Matrix4x4 matrix(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);
	Matrix4x4 expected(
		2, 4, 6, 8,
		10, 12, 14, 16,
		18, 20, 22, 24,
		26, 28, 30, 32);

	Matrix4x4 result = op * matrix;

	EXPECT_MAT3_EQ(expected, result);
}

TEST(Matrix4x4, VectorMultiplication)
{
	Matrix4x4 op(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);
	Vector4 vec(7, -6, 2, -1);
	Vector4 expected = Vector4(7, 35, 63, 91) 
		+ Vector4(-12, -36, -60, -84) 
		+ Vector4(6, 14, 22, 30)
		+ Vector4(-4, -8, -12, -16);

	Vector4 result = op * vec;
	EXPECT_VEC2_EQ(expected, result);
}

TEST(Matrix4x4, MatrixMultiplication)
{
	Matrix4x4 left(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);
	Matrix4x4 right(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);
	Matrix4x4 expected(
		90, 100, 110, 120,
		202, 228, 254, 280,
		314, 356, 398, 440,
		426, 484, 542, 600);

	Matrix4x4 result = left * right;
	EXPECT_MAT3_EQ(expected, result);

	expected = Matrix4x4(
		90, 100, 110, 120,
		202, 228, 254, 280,
		314, 356, 398, 440,
		426, 484, 542, 600);
	Matrix4x4 result2 = right * left;
	EXPECT_MAT3_EQ(expected, result2);
}

TEST(Matrix4x4, IdentityMultiplication)
{
	Matrix4x4 identity;
	Matrix4x4 matrix(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);

	Matrix4x4 result = identity * matrix;
	EXPECT_MAT4_EQ(matrix, result);

	result = matrix * identity;
	EXPECT_MAT4_EQ(matrix, result);
}

TEST(Matrix4x4, Rotate)
{
	Vector3 eulerAngles(45, 90, 54);
	Matrix3x3 rotate3 = Matrix3x3::rotate(eulerAngles);
	Matrix4x4 rotate4 = Matrix4x4::rotate(eulerAngles);

	EXPECT_MAT3_EQ(rotate3, rotate4.getMatrix3x3());
}

TEST(Matrix4x4, Translate)
{
	Vector3 position(1, 2, 3);
	Vector3 translation(6, -44, 14);
	Vector4 expected(7, -42, 17);

	Vector4 result = Matrix4x4::translate(translation) * Vector4(position);

	EXPECT_VEC4_EQ(expected, result);
}

TEST(Matrix4x4, Scale)
{
	Vector3 vec(1, 2, 3);
	Vector3 scale(-2, 5, 0.5);
	Vector4 expected(-2, 10, 1.5);

	Vector4 result = Matrix4x4::scale(scale) * vec;

	EXPECT_VEC4_EQ(expected, result);
}

TEST(Matrix4x4, mat4ToMatrix4x4)
{
	Matrix4x4 mat4x4;
	glm::mat4 mat4(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);

	Matrix4x4 expected4x4(
		1, 5, 9, 13,
		2, 6, 10, 14,
		3, 7, 11, 15,
		4, 8, 12, 16);

	mat4ToMatrix4x4(mat4, mat4x4);

	EXPECT_MAT4_EQ(expected4x4, mat4x4);
}

TEST(Matrix4x4, Perspective)
{
	float fov = 120.0f;
	float aspectRatio = 1.333333f;
	float zNear = 0.1f;
	float zFar = 100.0f;

	Matrix4x4 perspective = Matrix4x4::perspective(fov, aspectRatio, zNear, zFar);
	glm::mat4 glmPerspective = glm::perspective(fov, aspectRatio, zNear, zFar);
	Matrix4x4 expectedPerspective;

	mat4ToMatrix4x4(glmPerspective, expectedPerspective);

	EXPECT_MAT4_EQ(expectedPerspective, perspective);
}

TEST(Matrix4x4, LookAt)
{
	glm::vec3 glmCameraPos(1, 1, 1);
	glm::vec3 glmTarget(0, 0, 0);
	glm::vec3 glmUp(0, 1, 0);

	Vector3 cameraPos, target, up;
	vec3ToVector3(glmCameraPos, cameraPos);
	vec3ToVector3(glmTarget, target);
	vec3ToVector3(glmUp, up);

	Matrix4x4 lookAt = Matrix4x4::lookAt(cameraPos, target, up);
	glm::mat4 glmLookAt = glm::lookAt(glmCameraPos, glmTarget, glmUp);
	Matrix4x4 expectedLookAt;
	mat4ToMatrix4x4(glmLookAt, expectedLookAt);

	EXPECT_MAT4_EQ(expectedLookAt, lookAt);
}

void vec3ToVector3(const glm::vec3& vec3, Vector3& vector3)
{
	vector3.x = vec3.x;
	vector3.y = vec3.y;
	vector3.z = vec3.z;
}

void mat4ToMatrix4x4(const glm::mat4& mat4, Matrix4x4& mat4x4)
{
	mat4x4.c0r0 = mat4[0][0];
	mat4x4.c0r1 = mat4[0][1];
	mat4x4.c0r2 = mat4[0][2];
	mat4x4.c0r3 = mat4[0][3];
	mat4x4.c1r0 = mat4[1][0];
	mat4x4.c1r1 = mat4[1][1];
	mat4x4.c1r2 = mat4[1][2];
	mat4x4.c1r3 = mat4[1][3];
	mat4x4.c2r0 = mat4[2][0];
	mat4x4.c2r1 = mat4[2][1];
	mat4x4.c2r2 = mat4[2][2];
	mat4x4.c2r3 = mat4[2][3];
	mat4x4.c3r0 = mat4[3][0];
	mat4x4.c3r1 = mat4[3][1];
	mat4x4.c3r2 = mat4[3][2];
	mat4x4.c3r3 = mat4[3][3];
}

#endif //MATH_TESTS