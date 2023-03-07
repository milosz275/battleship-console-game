#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H

#include <iostream>

class Exception
{
	// the error message
	std::string error;
public:
	// initialised the error with its message
	Exception(std::string e);
	friend std::ostream& operator<<(std::ostream& os, const Exception& e);
};

#endif