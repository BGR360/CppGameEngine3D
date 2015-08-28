#ifndef BENGINE_INVALID_OPERATION_EXCEPTION_H
#define BENGINE_INVALID_OPERATION_EXCEPTION_H

#include <Engine.h>

#include <sstream>

#include <exceptions/BengineException.h>

namespace Exceptions
{
	class ENGINE_DLL_EXPORT_IMPORT InvalidOperationException : public BengineException
	{
		string m_operation;
		string m_operand;
		string m_reason;

	public:
		InvalidOperationException()
			: m_operation(""), m_operand(""), m_reason("") {}
		InvalidOperationException(string operation, string operandName, string reason)
			: m_operation(operation), m_operand(operandName), m_reason(reason) {}
		virtual ~InvalidOperationException() {}

		inline virtual const char* what() const throw()
		{
			return "InvalidOperationException";
		}

		inline virtual string message() const throw()
		{
			stringstream ret;

			ret << "Cannot perform '" << m_operation
				<< "' on object (type = '" << m_operand << "'). "
				<< "Reason: " << m_reason;

			return ret.str();
		}
	};
}

#endif //BENGINE_INVALID_OPERATION_EXCEPTION_H