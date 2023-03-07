#include <Exception.h>

Exception::Exception(std::string e) : error(e) {};

std::ostream& operator<<(std::ostream& os, const Exception& e) { return os << "Exception: " << e.error << std::endl; }