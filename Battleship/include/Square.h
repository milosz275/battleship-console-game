#ifndef SQUARE_H
#define SQUARE_H

#include "Exception.h"
#include "include/Ship.h"

namespace Battleship
{
	class Square
	{
		// pointer to the ship set in the square
		Ship* ship;
		// flag indicating if the square were shot at
		bool isHit;
	public:
		// initialises the square
		Square();
		// returns true if the square contains a ship, false respectively
		bool check_if_contains_ship(void);
		// returns true if the square were already shot at, false respectively
		bool check_if_hit(void);
		// returns the ship from the square
		Ship* getShip(void);
		// increments hit counts of the ship contained in the square
		void setHit(void);
		// sets the ship into the square
		void setShip(Ship& S);
		// deletes the ship which the square contains
		void deleteShip(void);
		// prints the square to the given stream
		friend std::ostream& operator<<(std::ostream& os, const Square& S);
	};
}

#endif