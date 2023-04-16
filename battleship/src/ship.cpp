#include "include/ship.h"

namespace battleship
{
	ship::ship(int size, std::string name) : m_size(size), m_hits(0), m_name(name) { assert(m_size > 0 && m_size <= 10); };

	int ship::get_size(void) { return m_size; }

	int ship::get_hits(void) { return m_hits; }

	const ship* ship::operator++() { m_hits++; return this; }

	std::string ship::get_name(void) { return m_name; }

	bool ship::operator==(const ship* ship) { return m_name == ship->m_name; }

	std::ostream& operator<<(std::ostream& os, const ship* ship) { return os << "ship name: " << ship->m_name << "\t size: " << ship->m_size << "\t hits: " << ship->m_hits << std::endl; }
}