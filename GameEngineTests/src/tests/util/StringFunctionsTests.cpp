#include <Testing.h>

#include <vector>

#include <util/StringFunctions.h>

using std::vector;
using namespace Util;

TEST(StringFunctions, SplitString)
{
	string str = "489.fff I don't really know.// yo";

	vector<string> result;

	string elem0, elem1, elem2, elem3, elem4, elem5;

	//Split at '.'
	splitString(str, '.', result);
	elem0 = "489";
	elem1 = "fff I don't really know";
	elem2 = "// yo";
	EXPECT_EQ(elem0, result[0]);
	EXPECT_EQ(elem1, result[1]);
	EXPECT_EQ(elem2, result[2]);

	result.clear();

	//Split at ' '
	splitString(str, ' ', result);
	elem0 = "489.fff";
	elem1 = "I";
	elem2 = "don't";
	elem3 = "really";
	elem4 = "know.//";
	elem5 = "yo";
	EXPECT_EQ(elem0, result[0]);
	EXPECT_EQ(elem1, result[1]);
	EXPECT_EQ(elem2, result[2]);
	EXPECT_EQ(elem3, result[3]);
	EXPECT_EQ(elem4, result[4]);
	EXPECT_EQ(elem5, result[5]);

	result.clear();

	//Split at '/'
	splitString(str, '/', result);
	elem0 = "489.fff I don't really know.";
	elem1 = " yo";
	EXPECT_EQ(elem0, result[0]);
	EXPECT_EQ(elem1, result[1]);
}

TEST(StringFunctions, StringToInt)
{
	string str_a = "1";
	string str_b = "69696969";
	string str_c = "-42";
	string str_d = "15.992";

	int a = stringToInt(str_a);
	int b = stringToInt(str_b);
	int c = stringToInt(str_c);
	int d = stringToInt(str_d);

	int expected_a = 1;
	int expected_b = 69696969;
	int expected_c = -42;
	int expected_d = 15;

	EXPECT_EQ(expected_a, a);
	EXPECT_EQ(expected_b, b);
	EXPECT_EQ(expected_c, c);
	EXPECT_EQ(expected_d, d);
}

TEST(StringFunctions, StringToDouble)
{
	string str_a = "15490208.333255";
	string str_b = "69696969";
	string str_c = "-42.1234543";
	string str_d = "15.992";

	double a = stringToDouble(str_a);
	double b = stringToDouble(str_b);
	double c = stringToDouble(str_c);
	double d = stringToDouble(str_d);

	double expected_a = 15490208.333255;
	double expected_b = 69696969;
	double expected_c = -42.1234543;
	double expected_d = 15.992;

	EXPECT_DOUBLE_EQ(expected_a, a);
	EXPECT_DOUBLE_EQ(expected_b, b);
	EXPECT_DOUBLE_EQ(expected_c, c);
	EXPECT_DOUBLE_EQ(expected_d, d);
}

TEST(StringFunctions, StringToFloat)
{
	string str_a = "108.333";
	string str_b = "696969";
	string str_c = "-42.1234543";
	string str_d = "15.992";

	float a = stringToFloat(str_a);
	float b = stringToFloat(str_b);
	float c = stringToFloat(str_c);
	float d = stringToFloat(str_d);

	float expected_a = 108.333;
	float expected_b = 696969;
	float expected_c = -42.1234543;
	float expected_d = 15.992;

	EXPECT_FLOAT_EQ(expected_a, a);
	EXPECT_FLOAT_EQ(expected_b, b);
	EXPECT_FLOAT_EQ(expected_c, c);
	EXPECT_FLOAT_EQ(expected_d, d);
}

TEST(StringFunctions, GetFileNameFromPath)
{
	string filePath("./res/images/thisIsMyName.png");
	string expectedName("thisIsMyName.png");

	string name = getFileNameFromPath(filePath);

	EXPECT_EQ(expectedName, name);
}

TEST(StringFunctions, RemoveExtensionFromFileName)
{
	string fileName("thisIsMyName.lmnop");
	string expected("thisIsMyName");

	string result = removeExtensionFromFileName(fileName);

	EXPECT_EQ(expected, result);
}

TEST(StringFunctions, GetFileExtension)
{
	string filePath("./res/images/bigbooty.jpg");
	string expected("jpg");
	string result = getFileExtension(filePath);

	EXPECT_EQ(expected, result);
}