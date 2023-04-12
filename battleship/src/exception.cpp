#include "include/Exception.h"

namespace game_exceptions
{
	exception::exception(std::string error, int code) : runtime_error(error.c_str()), m_code(code) {};

	std::ostream& operator<<(std::ostream& os, const exception& exception) { return os << "Exception: " << exception.what() << std::endl; }
}