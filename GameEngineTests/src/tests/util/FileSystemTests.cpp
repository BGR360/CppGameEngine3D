#include <Testing.h>

#include <fstream>

#include <util/filesys/FileSystem.h>

using std::ifstream;

using Util::FileSystem;

TEST(FileSystem, Path)
{
	FileSystem& filesys = FileSystem::getInstance();

	string relativePath = "./res/images/image.jpg";
	string expectedPath;

	ifstream path;
	path.open("path.txt");

	if (path.fail())
	{
		expectedPath = relativePath;
	}
	else
	{
		expectedPath = string("./../TestGame") + relativePath.substr(1);
	}

	string result = filesys.path(relativePath);

	EXPECT_EQ(expectedPath, result);
}