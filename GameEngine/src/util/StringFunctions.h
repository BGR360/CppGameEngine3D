#ifndef BENGINE_STRING_FUNCTIONS_H
#define BENGINE_STRING_FUNCTIONS_H

#include <Engine.h>

#include <string>
#include <vector>

#include <qt/QtCore/qstring.h>

using std::string;
using std::vector;

//Util functions are private to the engine and will not be exposed to the dll-interface

namespace Util
{
	//Splits a string into a vector of strings, using delim as the delimiting character
	void ENGINE_DLL_TESTING_ONLY splitString(const string& str, char delim, vector<string>& elems);

	//String conversion functions
	int ENGINE_DLL_TESTING_ONLY stringToInt(const string& str);
	float ENGINE_DLL_TESTING_ONLY stringToFloat(const string& str);
	double ENGINE_DLL_TESTING_ONLY stringToDouble(const string& str);

	string ENGINE_DLL_TESTING_ONLY getFileNameFromPath(const string& filePath);
	string ENGINE_DLL_TESTING_ONLY removeExtensionFromFileName(const string& fileName);
	string ENGINE_DLL_TESTING_ONLY getFileExtension(const string& filePath);

	void ENGINE_DLL_EXPORT_IMPORT qStringToStdString(const QString& qstr, string& str);
	void ENGINE_DLL_EXPORT_IMPORT qStringToStdString(QStringRef qstrref, string& str);
	string ENGINE_DLL_EXPORT_IMPORT qStringToStdString(const QString& qstr);
	string ENGINE_DLL_EXPORT_IMPORT qStringToStdString(QStringRef qstrref);
}

#endif //BENGINE_STRING_FUNCTIONS_H
