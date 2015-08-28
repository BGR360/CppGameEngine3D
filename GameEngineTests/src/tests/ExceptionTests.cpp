#include <Testing.h>

#include <iostream>

#include <exceptions/BengineException.h>
#include <exceptions/FileException.h>
#include <exceptions/FileNotFoundException.h>
#include <exceptions/InvalidOperationException.h>

using std::string;

using namespace Exceptions;

TEST(Exceptions, BengineException)
{
	string expectedWhat = "BengineException";
	string actualWhat;
	string expectedMessage = "An error occurred.";
	string actualMessage;

	try
	{
		throw BengineException("An error occurred.");
	}
	catch (BengineException& e)
	{
		actualWhat = e.what();
		actualMessage = e.message();
	}

	EXPECT_EQ(expectedWhat, actualWhat);
	EXPECT_EQ(expectedMessage, actualMessage);

	try
	{
		throw BengineException("An error occurred.");
	}
	catch (exception& e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
		actualWhat = e.what();
	}

	EXPECT_EQ(expectedWhat, actualWhat);
}

TEST(Exceptions, BengineException_NoArg)
{
	string expectedWhat = "BengineException";
	string actualWhat;
	string expectedMessage = "No error information available.";
	string actualMessage;

	try
	{
		throw BengineException();
	}
	catch (BengineException& e)
	{
		actualWhat = e.what();
		actualMessage = e.message();
	}

	EXPECT_EQ(expectedWhat, actualWhat);
	EXPECT_EQ(expectedMessage, actualMessage);

	try
	{
		throw BengineException();
	}
	catch (exception& e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
		actualWhat = e.what();
	}

	EXPECT_EQ(expectedWhat, actualWhat);
}

TEST(Exceptions, FileException)
{
	string filePath = "./folder/another folder/thisFileAintHere.lol";

	string expectedWhat = "FileException";
	string actualWhat;
	string expectedMessage = "An error occurred while reading the file ./folder/another folder/thisFileAintHere.lol";
	string actualMessage;

	try
	{
		throw FileException(filePath);
	}
	catch (BengineException& e)
	{
		actualWhat = e.what();
		actualMessage = e.message();
	}

	EXPECT_EQ(expectedWhat, actualWhat);
	EXPECT_EQ(expectedMessage, actualMessage);
}

TEST(Exceptions, FileException_NoArg)
{
	string filePath = "./folder/another folder/thisFileAintHere.lol";

	string expectedWhat = "FileException";
	string actualWhat;
	string expectedMessage = "An error occurred while reading the file.";
	string actualMessage;

	try
	{
		throw FileException();
	}
	catch (BengineException& e)
	{
		actualWhat = e.what();
		actualMessage = e.message();
	}

	EXPECT_EQ(expectedWhat, actualWhat);
	EXPECT_EQ(expectedMessage, actualMessage);
}

TEST(Exceptions, FileNotFoundException)
{
	string filePath = "./folder/another folder/thisFileAintHere.lol";

	string expectedWhat = "FileNotFoundException";
	string actualWhat;
	string expectedMessage = "Could not locate file ./folder/another folder/thisFileAintHere.lol";
	string actualMessage;

	try
	{
		throw FileNotFoundException(filePath);
	}
	catch (BengineException& e)
	{
		actualWhat = e.what();
		actualMessage = e.message();
	}

	EXPECT_EQ(expectedWhat, actualWhat);
	EXPECT_EQ(expectedMessage, actualMessage);
}

TEST(Exceptions, FileNotFoundException_NoArg)
{
	string expectedWhat = "FileNotFoundException";
	string actualWhat;
	string expectedMessage = "Could not locate file.";
	string actualMessage;

	try
	{
		throw FileNotFoundException();
	}
	catch (FileNotFoundException& e)
	{
		actualWhat = e.what();
		actualMessage = e.message();
	}

	EXPECT_EQ(expectedWhat, actualWhat);
	EXPECT_EQ(expectedMessage, actualMessage);
}

TEST(Exceptions, InvalidOperationException)
{
	string operation = "add";
	string operand = "Thingy";
	string reason = "You can't add two Thingies.";

	string expectedWhat = "InvalidOperationException";
	string actualWhat;
	string expectedMessage = "Cannot perform 'add' on object (type = 'Thingy'). Reason: You can't add two Thingies.";
	string actualMessage;

	try
	{
		throw InvalidOperationException(operation, operand, reason);
	}
	catch (BengineException& e)
	{
		actualWhat = e.what();
		actualMessage = e.message();
	}

	EXPECT_EQ(expectedWhat, actualWhat);
	EXPECT_EQ(expectedMessage, actualMessage);
}