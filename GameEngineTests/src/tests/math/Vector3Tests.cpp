#include <Testing.h>

#include <math/Vector3.h>

using Math::Vector3;

#define FLOAT_THRESHOLD 0.00001f;

#ifdef MATH_TESTS

TEST(Vector3, VectorConstruction)
{
	Vector3 test(95834.388f, -597.46f, 99.12345f);
	EXPECT_FLOAT_EQ(test.x, 95834.388f);
	EXPECT_FLOAT_EQ(test.y, -597.46f);
	EXPECT_FLOAT_EQ(test.z, 99.12345f);
}

TEST(Vector3, VectorAddition)
{
	Vector3 left(1.0f, -233.0f, 1.234f);
	Vector3 right(0.0f, +1.0f, 2.0f);
	Vector3 result = left + right;
	Vector3 expected(1.0f, -232.0f, 3.234f);

	EXPECT_VEC3_EQ(expected, result);
}

TEST(Vector3, VectorSubtraction)
{
	Vector3 left(1.0f, -233.0f, 1.234f);
	Vector3 right(0.0f, +1.0f, 2.0f);
	Vector3 result = left - right;
	Vector3 expected(1.0f, -234.0f, -0.766f);

	EXPECT_VEC3_EQ(expected, result);
}

TEST(Vector3, ScalarMultiplication)
{
	float scalar = 3.5f;
	Vector3 vec(0.0f, +1.0f, 2.0f);
	Vector3 result = scalar * vec;
	Vector3 expected(0.0f, 3.5f, 7.0f);

	EXPECT_VEC3_EQ(expected, result);

	result = vec * scalar;

	EXPECT_VEC3_EQ(expected, result);
}

TEST(Vector3, VectorMultiplication)
{
	Vector3 left(1.0f, -3.5f, 27234.348f);
	Vector3 right(875.33333f, 0.0f, -1.0f);

	Vector3 expected(875.33333f, 0.0f, -27234.348f);
	Vector3 result = left * right;

	EXPECT_VEC3_EQ(expected, result);
}

TEST(Vector3, ScalarDivision)
{
	float scalar = 3.5f;
	Vector3 vec(0.0f, +1.0f, 2.0f);
	Vector3 result = vec / scalar;
	Vector3 expected(0.0f, 0.28571429f, 0.57142857f);

	EXPECT_VEC3_EQ(expected, result);
}

TEST(Vector3, VectorDivision)
{
	Vector3 left(1.0f, -3.5f, 27234.348f);
	Vector3 right(10.0f, 1.0f, -1.0f);

	Vector3 expected(0.1f, -3.5f, -27234.348f);
	Vector3 result = left / right;

	EXPECT_VEC3_EQ(expected, result);
}

TEST(Vector3, VectorCopyConstructor)
{
	Vector3 source(1.0f, 2.0f, 3.0f);
	Vector3 vec(source);

	EXPECT_VEC3_EQ(source, vec);
}

TEST(Vector3, Assignment_Uninitialized)
{
	Vector3 source(1.0f, 2.0f, 3.0f);
	Vector3 vec;

	vec = source;

	EXPECT_VEC3_EQ(source, vec);
}

TEST(Vector3, Assignment_Initialized)
{
	Vector3 source(1.0f, 2.0f, 3.0f);
	Vector3 vec(443.3f, 547.4f, 1.f);

	vec = source;

	EXPECT_VEC3_EQ(source, vec);
}

TEST(Vector3, PlusEqualsAssignment)
{
	Vector3 left(1.0f, 2.0f, 3.0f);
	Vector3 right(10.0f, 1.5f, 3.333f);
	Vector3 expected(11.0f, 3.5f, 6.333f);

	left += right;

	EXPECT_VEC3_EQ(expected, left);
}

TEST(Vector3, MinusEqualsAssignment)
{
	Vector3 left(1.0f, 2.0f, 3.0f);
	Vector3 right(10.0f, 1.5f, 3.333f);
	Vector3 expected(-9.0f, 0.5f, -0.333f);

	left -= right;

	EXPECT_VEC3_EQ(expected, left);

}

TEST(Vector3, TimesEqualsAssignment)
{
	Vector3 left(1.0f, 2.0f, 3.0f);
	Vector3 right(10.0f, 1.5f, 3.333333f);
	Vector3 expected(10.0f, 3.0f, 10.0f);

	left *= right;

	EXPECT_VEC3_EQ(expected, left);
}

TEST(Vector3, DivideEqualsAssignment)
{
	Vector3 left(1.0f, 2.0f, 3.0f);
	Vector3 right(10.0f, 1.5f, 3.0f);
	Vector3 expected(0.1f, 1.333333333f, 1.0f);

	left /= right;

	EXPECT_VEC3_EQ(expected, left);
}

TEST(Vector3, DotProduct)
{
	Vector3 left(1.0f, 2.0f, 3.0f);
	Vector3 rght(2.0f, 1.0f, -2.0f);

	float expected = 1.0f * 2.0f + 2.0f * 1.0f + 3.0f * -2.0f;
	float dot = Vector3::dot(left, rght);

	EXPECT_FLOAT_EQ(expected, dot);
}

TEST(Vector3, CrossProduct)
{
	Vector3 left(1.0f, 2.0f, -300.0f);
	Vector3 right(14.0f, -2.0f, 7.0f);

	Vector3 expected(-586.0f, -4207.0f, -30.0f);
	Vector3 cross = Vector3::cross(left, right);

	EXPECT_VEC3_EQ(expected, cross);
}

TEST(Vector3, Magnitude)
{
	Vector3 vec(3, 4, 5);
	float expected = 7.07107f;
	float result = vec.magnitude();

	EXPECT_FLOAT_CLOSE_ENOUGH(expected, result);
}

TEST(Vector3, Normalize)
{
	const Vector3 vec(1, 1, 0);
	Vector3 expected(1.0f/sqrt(2.0f), 1.0f/sqrt(2.0f), 0);

	Vector3 result = Vector3::normalize(vec);
	Vector3 result2 = vec.normalized();

	EXPECT_VEC3_CLOSE_ENOUGH(expected, result);
	EXPECT_VEC3_CLOSE_ENOUGH(expected, result2);
}

#endif //MATH_TESTS