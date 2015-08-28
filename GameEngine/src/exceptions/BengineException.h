#ifndef BENGINE_BENGINE_EXCEPTION_H
#define BENGINE_BENGINE_EXCEPTION_H

#include <Engine.h>

#include <exception>
#include <string>
#include <typeinfo>

using std::exception;
using std::string;
using std::stringstream;

namespace Exceptions
{
	class ENGINE_DLL_EXPORT_IMPORT BengineException : public exception
	{
		string m_message;

	public:
		BengineException() : m_message("No error information available.") {}
		BengineException(string message) : m_message(message) {}
		virtual ~BengineException() {}

		inline virtual const char* what() const throw()
		{
			return "BengineException";
		}

		inline virtual string message() const throw()
		{
			return m_message;
		}
	};
}

#endif //BENGINE_BENGINE_EXCEPTION_H