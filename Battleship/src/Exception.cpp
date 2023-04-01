#include "include/Exception.h"

Exception::Exception(std::string e, int t) : runtime_error(e.c_str()), code(t) {};

std::ostream& operator<<(std::ostream& os, const Exception& e) { return os << "Exception: " << e.what() << std::endl; }