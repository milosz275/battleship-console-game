#include "include/Ship.h"

namespace Battleship
{
	int Ship::getSize(void) { return m_size; }

	int Ship::getHits(void) { return m_hits; }

	const Ship* Ship::operator++() { m_hits++; return this; }

	std::string Ship::getName(void) { return m_name; }

	Ship::Ship(int size, std::string name) : m_name(name), m_hits(0) { assert(size > 0 && size <= 10); m_size = size; };

	bool Ship::operator==(const Ship* ship) { return m_name == ship->m_name; }

	std::ostream& operator<<(std::ostream& os, const Ship* ship) { return os << "ship name: " << ship->m_name << "\t size: " << ship->m_size << "\t hits: " << ship->m_hits << std::endl; }
}