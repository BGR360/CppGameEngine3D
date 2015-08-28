#ifndef BENGINE_FILE_SYSTEM_H
#define BENGINE_FILE_SYSTEM_H

#include <Engine.h>

#include <string>

using std::string;

//FileSystem is a Singleton, because we only need one FileSystem for the entire application

namespace Util
{
	class ENGINE_DLL_TESTING_ONLY FileSystem
	{
		string m_rootDir;

	public:
		static FileSystem& getInstance()
		{
			static FileSystem INSTANCE;
			return INSTANCE;
		}

		string path(const string& relativePath);

	private:
		FileSystem();

		FileSystem(const FileSystem& source) = delete;		//override copy ctor
		FileSystem& operator=(const FileSystem& source) = delete;	//override assignment operator
	};
}

#endif //BENGINE_FILE_SYSTEM_H