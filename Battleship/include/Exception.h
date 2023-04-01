#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H

#include <iostream>

class Exception : public std::runtime_error
{
	// the error code
	int code;
public:
	// initialises the error with its message
	Exception(std::string e, int t = 0);
	// prints the exception to the given stream
	friend std::ostream& operator<<(std::ostream& os, const Exception& e);
};

#endif