#include <gtest/gtest.h>

//#define OVERNIGHT_TESTS
//#define TEST_WINDOW_OPEN
//#define RANDOM_TESTS
#define RENDERING_TESTS
#define MATH_TESTS

#include <iostream>
using std::cout;
using std::endl;

#define FLOAT_THRESHOLD 0.000001f
#define DOUBLE_THRESHOLD 0.000001

#define PRINT_CLOSE_ENOUGH()
#define PRINT_NOT_CLOSE_ENOUGH(expected, actual) cout << "Difference: " << abs(expected - actual) << endl

#define EXPECT_FLOAT_CLOSE_ENOUGH(expected, actual) \
	{\
		bool floatIsWithinThreshold = abs(expected - actual) < FLOAT_THRESHOLD; \
		EXPECT_TRUE(floatIsWithinThreshold); \
		if(!floatIsWithinThreshold) \
				{ \
			PRINT_NOT_CLOSE_ENOUGH(expected, actual); \
				} \
				else \
		{ \
			PRINT_CLOSE_ENOUGH(); \
		} \
	}

#define EXPECT_DOUBLE_CLOSE_ENOUGH(expected, actual) \
	{\
		bool doubleIsWithinThreshold = abs(expected - actual) < DOUBLE_THRESHOLD; \
		EXPECT_TRUE(doubleIsWithinThreshold); \
		if(!doubleIsWithinThreshold) \
				{ \
			PRINT_NOT_CLOSE_ENOUGH(expected, actual); \
				} \
				else \
		{ \
			PRINT_CLOSE_ENOUGH(); \
		} \
	}

#define EXPECT_VEC3_EQ(expected, actual) \
	EXPECT_FLOAT_EQ(expected.x, actual.x); \
	EXPECT_FLOAT_EQ(expected.y, actual.y); \
	EXPECT_FLOAT_EQ(expected.z, actual.z)

#define EXPECT_VEC3_CLOSE_ENOUGH(expected, actual) \
	EXPECT_FLOAT_CLOSE_ENOUGH(expected.x, actual.x); \
	EXPECT_FLOAT_CLOSE_ENOUGH(expected.y, actual.y); \
	EXPECT_FLOAT_CLOSE_ENOUGH(expected.z, actual.z)

#define EXPECT_VEC2_EQ(expected, actual) \
	EXPECT_FLOAT_EQ(expected.x, actual.x); \
	EXPECT_FLOAT_EQ(expected.y, actual.y)

#define EXPECT_VEC4_EQ(expected, actual) \
	EXPECT_FLOAT_EQ(expected.x, actual.x); \
	EXPECT_FLOAT_EQ(expected.y, actual.y); \
	EXPECT_FLOAT_EQ(expected.z, actual.z); \
	EXPECT_FLOAT_EQ(expected.w, actual.w)

#define EXPECT_MAT2_EQ(expected, actual) \
	EXPECT_FLOAT_EQ(expected.c0r0, actual.c0r0); \
	EXPECT_FLOAT_EQ(expected.c0r1, actual.c0r1); \
	EXPECT_FLOAT_EQ(expected.c1r0, actual.c1r0); \
	EXPECT_FLOAT_EQ(expected.c1r1, actual.c1r1)

#define EXPECT_MAT3_EQ(expected, actual) \
	EXPECT_FLOAT_EQ(expected.c0r0, actual.c0r0); \
	EXPECT_FLOAT_EQ(expected.c0r1, actual.c0r1); \
	EXPECT_FLOAT_EQ(expected.c0r2, actual.c0r2); \
	EXPECT_FLOAT_EQ(expected.c1r0, actual.c1r0); \
	EXPECT_FLOAT_EQ(expected.c1r1, actual.c1r1); \
	EXPECT_FLOAT_EQ(expected.c1r2, actual.c1r2); \
	EXPECT_FLOAT_EQ(expected.c2r0, actual.c2r0); \
	EXPECT_FLOAT_EQ(expected.c2r1, actual.c2r1); \
	EXPECT_FLOAT_EQ(expected.c2r2, actual.c2r2)

#define EXPECT_MAT4_EQ(expected, actual) \
	EXPECT_FLOAT_EQ(expected.c0r0, actual.c0r0); \
	EXPECT_FLOAT_EQ(expected.c0r1, actual.c0r1); \
	EXPECT_FLOAT_EQ(expected.c0r2, actual.c0r2); \
	EXPECT_FLOAT_EQ(expected.c0r3, actual.c0r3); \
	EXPECT_FLOAT_EQ(expected.c1r0, actual.c1r0); \
	EXPECT_FLOAT_EQ(expected.c1r1, actual.c1r1); \
	EXPECT_FLOAT_EQ(expected.c1r2, actual.c1r2); \
	EXPECT_FLOAT_EQ(expected.c1r3, actual.c1r3); \
	EXPECT_FLOAT_EQ(expected.c2r0, actual.c2r0); \
	EXPECT_FLOAT_EQ(expected.c2r1, actual.c2r1); \
	EXPECT_FLOAT_EQ(expected.c2r2, actual.c2r2); \
	EXPECT_FLOAT_EQ(expected.c2r3, actual.c2r3); \
	EXPECT_FLOAT_EQ(expected.c3r0, actual.c3r0); \
	EXPECT_FLOAT_EQ(expected.c3r1, actual.c3r1); \
	EXPECT_FLOAT_EQ(expected.c3r2, actual.c3r2); \
	EXPECT_FLOAT_EQ(expected.c3r3, actual.c3r3)