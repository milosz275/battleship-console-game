#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H

#include <iostream>

namespace game_exceptions
{
	class exception : public std::runtime_error
	{
		// the error code
		int m_code;
	public:
		// initialises the error with its message
		exception(std::string error, int code = 0);
		// prints the exception to the given stream
		friend std::ostream& operator<<(std::ostream& os, const exception& exception);
	};
}

#endif