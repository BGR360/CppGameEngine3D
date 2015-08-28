#include <Testing.h>

#include <math/Matrix3x3.h>
#include <math/Vector3.h>

using Math::Matrix3x3;
using Math::Vector3;

#ifdef MATH_TESTS

TEST(Matrix3x3, Identity)
{
	Matrix3x3 identity;

	Matrix3x3 expected(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);

	EXPECT_MAT3_EQ(expected, identity);
}

TEST(Matrix3x3, ConstructFrom2x2)
{
	Matrix2x2 matrix2x2(
		1, 2,
		3, 4);
	Matrix3x3 matrix(matrix2x2);
	Matrix3x3 expected(
		1, 2, 0,
		3, 4, 0,
		0, 0, 1);

	EXPECT_MAT3_EQ(expected, matrix);
}

TEST(Matrix3x3, Addition)
{
	Matrix3x3 left(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Matrix3x3 right(
		5, 2, 4,
		-5, 4, -1,
		2, 3, -7);
	Matrix3x3 expected(
		6, 4, 7,
		-1, 9, 5,
		9, 11, 2);

	Matrix3x3 result = left + right;
	EXPECT_MAT3_EQ(expected, result);
}

TEST(Matrix3x3, Subtraction)
{
	Matrix3x3 left(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Matrix3x3 right(
		5, 2, 4,
		-5, 4, -1,
		2, 3, -7);
	Matrix3x3 expected(
		-4, 0, -1,
		9, 1, 7,
		5, 5, 16);

	Matrix3x3 result = left - right;
	EXPECT_MAT3_EQ(expected, result);
}

TEST(Matrix3x3, ScalarMultiplication)
{
	float op = 2.0f;
	Matrix3x3 matrix(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Matrix3x3 expected(
		2, 4, 6,
		8, 10, 12,
		14, 16, 18);

	Matrix3x3 result = op * matrix;

	EXPECT_MAT3_EQ(expected, result);
}

TEST(Matrix3x3, VectorMultiplication)
{
	Matrix3x3 op(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Vector3 vec(7, -6, 2);
	Vector3 expected = Vector3(7, 28, 49) + Vector3(-12, -30, -48) + Vector3(6, 12, 18);

	Vector3 result = op * vec;
	EXPECT_VEC2_EQ(expected, result);
}

TEST(Matrix3x3, MatrixMultiplication)
{
	Matrix3x3 left(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Matrix3x3 right(
		5, 2, 4,
		-5, 4, -1,
		2, 3, -7);
	Matrix3x3 expected(
		1, 19, -19,
		7, 46, -31,
		13, 73, -43);

	Matrix3x3 result = left * right;
	EXPECT_MAT3_EQ(expected, result);

	expected = Matrix3x3(
		41, 52, 63,
		4, 2, 0,
		-35, -37, -39);
	Matrix3x3 result2 = right * left;
	EXPECT_MAT3_EQ(expected, result2);
}

TEST(Matrix3x3, IdentityMultiplication)
{
	Matrix3x3 identity;
	Matrix3x3 matrix(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);

	Matrix3x3 result = identity * matrix;
	EXPECT_MAT3_EQ(matrix, result);

	result = matrix * identity;
	EXPECT_MAT3_EQ(matrix, result);
}

TEST(Matrix3x3, Adjugate)
{
	Matrix3x3 matrix(
		1, 2, 3,
		4, 4, 6,
		7, 8, 9);
	Matrix3x3 expected(
		-12, 6, 0,
		6, -12, 6,
		4, 6, -4);

	Matrix3x3 result = Matrix3x3::adjugate(matrix);
	EXPECT_MAT3_EQ(expected, result);
}

TEST(Matrix3x3, Adjugate2)
{
	Matrix3x3 matrix(
		2, 4, -1,
		3, 1, 0,
		0, 5, -2);
	Matrix3x3 expected(
		-2, 3, 1,
		6, -4, -3,
		15, -10, -10);

	Matrix3x3 result = Matrix3x3::adjugate(matrix);
	EXPECT_MAT3_EQ(expected, result);
}

TEST(Matrix3x3, Determinant)
{
	Matrix3x3 matrix(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	float expected = 0.0f;

	float result = Matrix3x3::determinant(matrix);

	EXPECT_FLOAT_EQ(expected, result);
}

TEST(Matrix3x3, Inverse)
{
	Matrix3x3 matrix(
		1, 2, 3,
		4, 4, 6,
		7, 8, 9);
	Matrix3x3 expected(
		-1, 0.5f, 0,
		0.5, -1, 0.5f,
		0.333333333f, 0.5f, -0.333333333f);

	Matrix3x3 result = Matrix3x3::inverse(matrix);

	EXPECT_MAT3_EQ(expected, result);
}

TEST(Matrix3x3, Transpose)
{
	Matrix3x3 matrix(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Matrix3x3 expected(
		1, 4, 7,
		2, 5, 8,
		3, 6, 9);

	Matrix3x3 result = Matrix3x3::transpose(matrix);
	EXPECT_MAT3_EQ(expected, result);
}

TEST(Matrix3x3, RotateX)
{
	Vector3 yvec(0, 2, 0);
	Matrix3x3 op = Matrix3x3::rotate(45, Vector3(1, 0, 0));
	Vector3 expected(0, sqrt(2.0f), sqrt(2.0f));

	Vector3 result = op * yvec;

	EXPECT_VEC3_EQ(expected, result);
}

TEST(Matrix3x3, RotateY)
{
	Vector3 zvec(0, 0, 2);
	Matrix3x3 op = Matrix3x3::rotate(45, Vector3(0, 1, 0));
	Vector3 expected(sqrt(2.0f), 0, sqrt(2.0f));

	Vector3 result = op * zvec;

	EXPECT_VEC3_EQ(expected, result);
}

TEST(Matrix3x3, RotateZ)
{
	Vector3 xvec(2, 0, 0);
	Matrix3x3 op = Matrix3x3::rotate(45, Vector3(0, 0, 1));
	Vector3 expected(sqrt(2.0f), sqrt(2.0f), 0);

	Vector3 result = op * xvec;

	EXPECT_VEC3_EQ(expected, result);
}

TEST(Matrix3x3, RotateXY)
{
	Vector3 vec(0, 2, 0);
	Matrix3x3 opX = Matrix3x3::rotate(90, Vector3(1, 0, 0));
	Matrix3x3 opY = Matrix3x3::rotate(45, Vector3(0, 1, 0));
	Matrix3x3 op = opY * opX;
	Vector3 expected(sqrt(2.0f), 0, sqrt(2.0f));

	Vector3 result = op * vec;

	EXPECT_VEC3_CLOSE_ENOUGH(expected, result);
}

TEST(Matrix3x3, RotateXYZ)
{
	Vector3 vec(0, 3, 0);
	Matrix3x3 opX = Matrix3x3::rotate(90, Vector3(1, 0, 0));
	Matrix3x3 opY = Matrix3x3::rotate(90, Vector3(0, 1, 0));
	Matrix3x3 opZ = Matrix3x3::rotate(90, Vector3(0, 0, 1));
	Matrix3x3 op = opZ * opY * opX;
	Vector3 expected(0, 3, 0);

	Vector3 result = op * vec;

	EXPECT_VEC3_CLOSE_ENOUGH(expected, result);
}

TEST(Matrix3x3, Tilde)
{
	Vector3 a(1, 0, 0);
	Vector3 b(0, 0, 1);

	Vector3 expected(0, -1, 0);
	Vector3 c_cross = Vector3::cross(a, b);
	Vector3 c_tilde;

	Matrix3x3 tilde = Matrix3x3::tilde(a);
	c_tilde = tilde * b;

	EXPECT_VEC3_EQ(expected, c_cross);
	EXPECT_VEC3_EQ(expected, c_tilde);
}

TEST(Matrix3x3, AngleAxis)
{
	Vector3 vec(sqrt(2.0f), 0, sqrt(2.0f));
	Vector3 axis(sqrt(2.0f), 0, -sqrt(2.0f));
	Matrix3x3 op = Matrix3x3::rotate(45, axis);
	Vector3 expected(1, -sqrt(2.0f), 1);

	Vector3 result = op * vec;

	EXPECT_VEC3_EQ(expected, result);
}

TEST(Matrix3x3, Translate)
{
	Vector2 position(1, 2);
	Vector2 translation(5, -5);

	Vector3 result = Matrix3x3::translate(translation) * Vector3(position);
	Vector3 expected(6, -3, 1);

	EXPECT_VEC3_EQ(expected, result);
}

TEST(Matrix3x3, Scale)
{
	Vector3 vec(1, 2, 3);
	Vector3 scale(-2, 5, 0.5);
	Vector3 expected(-2, 10, 1.5);

	Vector3 result = Matrix3x3::scale(scale) * vec;

	EXPECT_VEC3_EQ(expected, result);
}

#endif // MATH_TESTS
