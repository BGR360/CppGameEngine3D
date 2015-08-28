#include "StringFunctions.h"

#include <cstdlib> //strtol(), strtod()
#include <sstream>

#include <util/Types.h>

using std::getline;
using std::stringstream;

namespace Util
{
	void splitString(const string& str, char delim, vector<string>& elems)
	{
		stringstream ss(str);
		string elem;
		while (getline(ss, elem, delim))
		{
			if (elem.length() > 0)
				elems.push_back(elem);
		}
	}

	int stringToInt(const string& str)
	{
		char* pEnd;
		return (int)strtol(str.c_str(), &pEnd, 10);
	}

	float stringToFloat(const string& str)
	{
		return (float)stringToDouble(str);
	}

	double stringToDouble(const string& str)
	{
		char* pEnd;
		return strtod(str.c_str(), &pEnd);
	}

	string getFileNameFromPath(const string& filePath)
	{
		//Derive the name of a file from its file path
		//e.g. ./res/meshes/testCube.obj yields a meshName of 'testCube'

		vector<string> elements;
		splitString(filePath, '/', elements);

		string fileName = elements[elements.size() - 1];
		elements.clear();

		return fileName;
	}

	string removeExtensionFromFileName(const string& fileName)
	{
		vector<string> fileNameElements;
		splitString(fileName, '.', fileNameElements);

		uint numCharsInExtension = 0;
		if (fileNameElements.size() > 1)
		{
			numCharsInExtension = fileNameElements[fileNameElements.size() - 1].length() + 1;
		}

		return fileName.substr(0, fileName.length() - numCharsInExtension);
	}

	string getFileExtension(const string& filePath)
	{
		string extension = "";

		string fileName = getFileNameFromPath(filePath);
		vector<string> fileNameElements;
		splitString(fileName, '.', fileNameElements);
		if (fileNameElements.size() > 1)
		{
			extension = fileNameElements[fileNameElements.size() - 1];
		}

		return extension;
	}

	void qStringToStdString(const QString& qstr, string& str)
	{
		str.clear();
		int length = qstr.length();
		str.reserve(length);
		for (int i = 0; i < length; i++)
		{
			char c = qstr.at(i).toLatin1();
			str.push_back(c);
		}
	}

	void qStringToStdString(QStringRef qstr, string& str)
	{
		str.clear();
		int length = qstr.length();
		str.reserve(length);
		for (int i = 0; i < length; i++)
		{
			char c = qstr.at(i).toLatin1();
			str.push_back(c);
		}
	}

	string qStringToStdString(const QString& qstr)
	{
		string ret;
		qStringToStdString(qstr, ret);
		return ret;
	}

	string qStringToStdString(QStringRef qstrref)
	{
		string ret;
		qStringToStdString(qstrref, ret);
		return ret;
	}
}