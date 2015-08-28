#include <Testing.h>

#include <math/Vector2.h>

using Math::Vector2;

#ifdef MATH_TESTS

TEST(Vector2, VectorConstruction)
{
	Vector2 test(95834.388f, -597.46f);
	EXPECT_FLOAT_EQ(test.x, 95834.388f);
	EXPECT_FLOAT_EQ(test.y, -597.46f);
}

TEST(Vector2, VectorAddition)
{
	Vector2 left(1.0f, -233.0f);
	Vector2 right(0.0f, +1.0f);
	Vector2 result = left + right;
	Vector2 expected(1.0f, -232.0f);

	EXPECT_VEC2_EQ(expected, result);
}

TEST(Vector2, VectorSubtraction)
{
	Vector2 left(1.0f, -233.0f);
	Vector2 right(0.0f, +1.0f);
	Vector2 result = left - right;
	Vector2 expected(1.0f, -234.0f);

	EXPECT_VEC2_EQ(expected, result);
}

TEST(Vector2, ScalarMultiplication)
{
	float scalar = 3.5f;
	Vector2 vec(0.0f, +1.0f);
	Vector2 result = scalar * vec;
	Vector2 expected(0.0f, 3.5f);

	EXPECT_VEC2_EQ(expected, result);

	result = vec * scalar;

	EXPECT_VEC2_EQ(expected, result);
}

TEST(Vector2, VectorMultiplication)
{
	Vector2 left(1.0f, -3.5f);
	Vector2 right(875.33333f, 0.0f);

	Vector2 expected(875.33333f, 0.0f);
	Vector2 result = left * right;

	EXPECT_VEC2_EQ(expected, result);
}

TEST(Vector2, ScalarDivision)
{
	float scalar = 3.5f;
	Vector2 vec(0.0f, +1.0f);
	Vector2 result = vec / scalar;
	Vector2 expected(0.0f, 0.28571429f);

	EXPECT_VEC2_EQ(expected, result);
}

TEST(Vector2, VectorDivision)
{
	Vector2 left(1.0f, -3.5f);
	Vector2 right(10.0f, 1.0f);

	Vector2 expected(0.1f, -3.5f);
	Vector2 result = left / right;

	EXPECT_VEC2_EQ(expected, result);
}

TEST(Vector2, VectorCopyConstructor)
{
	Vector2 source(1.0f, 2.0f);
	Vector2 vec(source);

	EXPECT_VEC2_EQ(source, vec);
}

TEST(Vector2, Assignment_Uninitialized)
{
	Vector2 source(1.0f, 2.0f);
	Vector2 vec;

	vec = source;

	EXPECT_VEC2_EQ(source, vec);
}

TEST(Vector2, Assignment_Initialized)
{
	Vector2 source(1.0f, 2.0f);
	Vector2 vec(443.3f, 547.4f);

	vec = source;

	EXPECT_VEC2_EQ(source, vec);
}

TEST(Vector2, PlusEqualsAssignment)
{
	Vector2 left(1.0f, 2.0f);
	Vector2 right(10.0f, 1.5f);
	Vector2 expected(11.0f, 3.5f);

	left += right;

	EXPECT_VEC2_EQ(expected, left);
}

TEST(Vector2, MinusEqualsAssignment)
{
	Vector2 left(1.0f, 2.0f);
	Vector2 right(10.0f, 1.5f);
	Vector2 expected(-9.0f, 0.5f);

	left -= right;

	EXPECT_VEC2_EQ(expected, left);

}

TEST(Vector2, TimesEqualsAssignment)
{
	Vector2 left(1.0f, 2.0f);
	Vector2 right(10.0f, 1.5f);
	Vector2 expected(10.0f, 3.0f);

	left *= right;

	EXPECT_VEC2_EQ(expected, left);
}

TEST(Vector2, DivideEqualsAssignment)
{
	Vector2 left(1.0f, 2.0f);
	Vector2 right(10.0f, 1.5f);
	Vector2 expected(0.1f, 1.33333333f);

	left /= right;

	EXPECT_VEC2_EQ(expected, left);
}

TEST(Vector2, DotProduct)
{
	Vector2 left(1.0f, 2.0f);
	Vector2 rght(2.0f, 1.0f);

	float expected = 1.0f * 2.0f + 2.0f * 1.0f;
	float dot = Vector2::dot(left, rght);

	EXPECT_FLOAT_EQ(expected, dot);
}

TEST(Vector2, Magnitude)
{
	Vector2 vec(3, 4);
	float expected = 5.0f;
	float result = vec.magnitude();

	EXPECT_FLOAT_EQ(expected, result);
}

TEST(Vector2, Normalize)
{
	const Vector2 vec(1, 1);
	Vector2 expected(1/sqrt(2.0f), 1/sqrt(2.0f));

	Vector2 result = Vector2::normalize(vec);
	Vector2 result2 = vec.normalized();

	EXPECT_VEC2_EQ(expected, result);
	EXPECT_VEC2_EQ(expected, result2);
}

#endif //MATH_TESTS