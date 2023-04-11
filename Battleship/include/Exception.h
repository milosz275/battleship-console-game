#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H

#include <iostream>

namespace GameExceptions
{
	class Exception : public std::runtime_error
	{
		// the error code
		int m_code;
	public:
		// initialises the error with its message
		Exception(std::string error, int code = 0);
		// prints the exception to the given stream
		friend std::ostream& operator<<(std::ostream& os, const Exception& exception);
	};
}

#endif