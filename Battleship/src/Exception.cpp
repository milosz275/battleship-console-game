#include <Exception.h>

Exception::Exception(std::string e) : exception(e.c_str()) {};

std::ostream& operator<<(std::ostream& os, const Exception& e) { return os << "Exception: " << e.what() << std::endl; }