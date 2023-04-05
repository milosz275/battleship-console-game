#include "include/Square.h"

namespace Battleship
{
	Square::Square() : ship(NULL), isHit(false) {};

	bool Square::check_if_contains_ship(void) { if (ship == NULL) return false; else return true; }

	bool Square::check_if_hit(void) { return isHit; }

	Ship* Square::getShip(void) { return ship; }

	void Square::setHit(void) { isHit = true; }

	void Square::setShip(Ship& S)
	{
		if (ship != NULL)
			throw GameExceptions::Exception("Tried to set a ship on a ship");
		ship = &S;
	}

	void Square::deleteShip(void) { delete ship; }

	std::ostream& operator<<(std::ostream& os, const Square& S)
	{
		if (S.isHit && S.ship != NULL)
			return os << "X";
		else if (S.isHit)
			return os << "/";
		else if (S.ship == NULL)
			return os << "-";
		else
			return os << "O";
	}
}