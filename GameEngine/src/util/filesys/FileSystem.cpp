#include "FileSystem.h"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::stringstream;

namespace Util
{
	FileSystem::FileSystem() : m_rootDir("")
	{
		//Try to open the 'path.txt' file in the executable's directory
		ifstream path;
		
		path.open("./path.txt");

		//Check for FileNotFound
		if (path.fail())
		{
			m_rootDir = ".";
		}
		else
		{
			char c;
			stringstream root;
			while (path >> c)
			{
				root << c;
			}
			m_rootDir = root.str();
		}
	}

	string FileSystem::path(const string& relativePath)
	{
		if (relativePath.at(0) == '.')
		{
			return m_rootDir + relativePath.substr(1);
		}
		else
		{
			return relativePath;
		}
	}
}