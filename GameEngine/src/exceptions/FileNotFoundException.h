#ifndef BENGINE_FILE_NOT_FOUND_EXCEPTION_H
#define BENGINE_FILE_NOT_FOUND_EXCEPTION_H

#include <Engine.h>

#include <exceptions/BengineException.h>

namespace Exceptions
{
	class ENGINE_DLL_EXPORT_IMPORT FileNotFoundException : public BengineException
	{
		string m_filePath;

	public:
		FileNotFoundException() : FileNotFoundException("") {}
		FileNotFoundException(string filePath) : m_filePath(filePath) {}
		virtual ~FileNotFoundException() {}

		inline virtual const char* what() const throw()
		{
			return "FileNotFoundException";
		}

		inline virtual string message() const throw()
		{
			if (m_filePath.compare("") != 0)
			{
				string ret = "Could not locate file ";
				ret += m_filePath;
				return ret;
			}
			else
			{
				return "Could not locate file.";
			}
		}
	};
}

#endif //BENGINE_FILE_NOT_FOUND_EXCEPTION_H