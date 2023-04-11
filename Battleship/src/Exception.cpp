#include "include/Exception.h"

namespace GameExceptions
{
	Exception::Exception(std::string error, int code) : runtime_error(error.c_str()), m_code(code) {};

	std::ostream& operator<<(std::ostream& os, const Exception& exception) { return os << "Exception: " << exception.what() << std::endl; }
}