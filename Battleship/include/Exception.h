#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H

#include <iostream>

class Exception
{
	// the error message
	std::string error;
public:
	// initialises the error with its message
	Exception(std::string e);
	// prints the exception to the given stream
	friend std::ostream& operator<<(std::ostream& os, const Exception& e);
};

#endif