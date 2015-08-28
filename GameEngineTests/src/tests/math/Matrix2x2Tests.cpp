#include <Testing.h>

#include <math/Matrix2x2.h>
#include <math/Vector2.h>

using Math::Matrix2x2;
using Math::Vector2;

#ifdef MATH_TESTS

TEST(Matrix2x2, Identity)
{
	Matrix2x2 identity;

	Matrix2x2 expected(
		1, 0,
		0, 1);

	EXPECT_MAT2_EQ(expected, identity);
}

TEST(Matrix2x2, Addition)
{
	Matrix2x2 left(
		1, 2,
		3, 4);
	Matrix2x2 right(
		5, 2,
		-5, 4);
	Matrix2x2 expected(
		6, 4,
		-2, 8);

	Matrix2x2 result = left + right;
	EXPECT_MAT2_EQ(expected, result);
}

TEST(Matrix2x2, Subtraction)
{
	Matrix2x2 left(
		1, 2,
		3, 4);
	Matrix2x2 right(
		5, 2,
		-5, 4);
	Matrix2x2 expected(
		-4, 0,
		8, 0);

	Matrix2x2 result = left - right;
	EXPECT_MAT2_EQ(expected, result);
}

TEST(Matrix2x2, ScalarMultiplication)
{
	float op = 2.0f;
	Matrix2x2 matrix(
		1, 2,
		3, 4);
	Matrix2x2 expected(
		2, 4,
		6, 8);

	Matrix2x2 result = op * matrix;

	EXPECT_MAT2_EQ(expected, result);
}

TEST(Matrix2x2, VectorMultiplication)
{
	Matrix2x2 op(
		1, 2,
		3, 4);
	Vector2 vec(7, -6);
	Vector2 expected(-5, -3);

	Vector2 result = op * vec;
	EXPECT_VEC2_EQ(expected, result);
}

TEST(Matrix2x2, MatrixMultiplication)
{
	Matrix2x2 left(
		1, 2,
		-3, 4);
	Matrix2x2 right(
		5, 2,
		1, -1);
	Matrix2x2 expected(
		7, 0,
		-11, -10);

	Matrix2x2 result = left * right;
	EXPECT_MAT2_EQ(expected, result);

	expected = Matrix2x2(
		-1, 18,
		4, -2);
	result = right * left;
	EXPECT_MAT2_EQ(expected, result);
}

TEST(Matrix2x2, IdentityMultiplication)
{
	Matrix2x2 identity;
	Matrix2x2 matrix(
		1, 2,
		3, 4);

	Matrix2x2 result = identity * matrix;
	EXPECT_MAT2_EQ(matrix, result);

	result = matrix * identity;
	EXPECT_MAT2_EQ(matrix, result);
}

TEST(Matrix2x2, Adjugate)
{
	Matrix2x2 matrix(
		1, 2,
		3, 4);
	Matrix2x2 expected(
		4, -2,
		-3, 1);

	Matrix2x2 result = Matrix2x2::adjugate(matrix);
	EXPECT_MAT2_EQ(expected, result);
}

TEST(Matrix2x2, Determinant)
{
	Matrix2x2 matrix(
		1, 2,
		3, 4);
	float expected = -2.0f;

	float result = Matrix2x2::determinant(matrix);

	EXPECT_FLOAT_EQ(expected, result);
}

TEST(Matrix2x2, Inverse)
{
	Matrix2x2 matrix(
		1, 2,
		3, 4);
	Matrix2x2 expected(
		-2, 1,
		1.5, -0.5);

	Matrix2x2 result = Matrix2x2::inverse(matrix);

	EXPECT_MAT2_EQ(expected, result);
}

TEST(Matrix2x2, Transpose)
{
	Matrix2x2 matrix(
		1, 2,
		3, 4);
	Matrix2x2 expected(
		1, 3,
		2, 4);

	Matrix2x2 result = Matrix2x2::transpose(matrix);
	EXPECT_MAT2_EQ(expected, result);
}

TEST(Matrix2x2, Rotate)
{
	Vector2 vector(2, 0);
	Matrix2x2 op = Matrix2x2::rotate(45);
	Vector2 expected(sqrt(2), sqrt(2));

	Vector2 result = op * vector;

	EXPECT_VEC2_EQ(expected, result);
}

TEST(Matrix2x2, Scale)
{
	Vector2 vec(-1, 3);
	Vector2 scale(2, 4);
	Vector2 expected(-2, 12);

	Vector2 result = Matrix2x2::scale(scale) * vec;

	EXPECT_VEC2_EQ(expected, result);
}
#endif // MATH_TESTS
