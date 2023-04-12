#include "include/Square.h"

namespace Battleship
{
	Square::Square() : m_ship(NULL), m_is_hit(false) {};

	bool Square::check_if_contains_ship(void) { if (m_ship == NULL) return false; else return true; }

	bool Square::check_if_hit(void) { return m_is_hit; }

	Ship* Square::getShip(void) { return m_ship; }

	void Square::setHit(void) { m_is_hit = true; }

	void Square::setShip(Ship& ship)
	{
		assert(m_ship == NULL);
		m_ship = &ship;
	}

	void Square::deleteShip(void) { delete m_ship; }

	std::ostream& operator<<(std::ostream& os, const Square& ship)
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