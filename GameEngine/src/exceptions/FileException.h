#ifndef BENGINE_FILE_EXCEPTION_H
#define BENGINE_FILE_EXCEPTION_H

#include <Engine.h>

#include <exceptions/BengineException.h>

namespace Exceptions
{
	class ENGINE_DLL_EXPORT_IMPORT FileException : public BengineException
	{
		string m_filePath;
		string m_message;

	public:
		FileException(string filePath = "", string message = "") : m_filePath(filePath), m_message("") {}
		virtual ~FileException() {}

		inline virtual const char* what() const throw()
		{
			return "FileException";
		}

		inline virtual string message() const throw()
		{
			string ret = "An error occurred while reading the file";
			
			if (m_filePath.compare("") == 0)
			{
				ret += '.';
			}
			else
			{
				ret += ' ';
				ret += m_filePath;
			}

			if (!(m_message.compare("") == 0))
			{
				ret += "\n";
				ret += m_message;
			}
			
			return ret;
		}
	};
}

#endif //BENGINE_FILE_EXCEPTION_H