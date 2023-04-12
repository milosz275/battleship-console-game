#ifndef SQUARE_H
#define SQUARE_H

#include "Exception.h"
#include "include/Ship.h"
#include <cassert>

namespace battleship
{
	class square
	{
		// pointer to the ship set in the square
		ship* m_ship;
		// flag indicating if the square were shot at
		bool m_is_hit;
	public:
		// initialises the square
		square();
		// returns true if the square contains a ship, false respectively
		bool check_if_contains_ship(void);
		// returns true if the square were already shot at, false respectively
		bool check_if_hit(void);
		// returns the ship from the square
		ship* get_ship(void);
		// increments hit counts of the ship contained in the square
		void set_hit(void);
		// sets the ship into the square
		void set_ship(ship& ship);
		// deletes the ship which the square contains
		void delete_ship(void);
		// prints the square to the given stream
		friend std::ostream& operator<<(std::ostream& os, const square& ship);
	};
}

#endif