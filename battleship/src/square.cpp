#include "include/square.h"

namespace battleship
{
	square::square() : m_ship(NULL), m_is_hit(false) {};

	bool square::check_if_contains_ship(void) { if (m_ship == NULL) return false; else return true; }

	bool square::check_if_hit(void) { return m_is_hit; }

	ship* square::get_ship(void) { return m_ship; }

	void square::set_hit(void) { m_is_hit = true; }

	void square::set_ship(ship& ship)
	{
		assert(m_ship == NULL);
		m_ship = &ship;
	}

	void square::delete_ship(void) { delete m_ship; }

	std::ostream& operator<<(std::ostream& os, const square& ship)
	{
		if (ship.m_is_hit && ship.m_ship != NULL)
			return os << "X";
		else if (ship.m_is_hit)
			return os << "/";
		else if (ship.m_ship == NULL)
			return os << "-";
		else
			return os << "O";
	}
}