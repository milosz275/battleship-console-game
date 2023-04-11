#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <string>
#include <cassert>

namespace Battleship
{
	class Ship
	{
		// size of the ship
		int m_size;
		// hits count
		int m_hits;
		// name of the ship
		std::string m_name;
	public:
		// creates a ship of a given size and name
		Ship(int size, std::string name);
		// returns size of the ship
		int getSize(void);
		// returns hits count
		int getHits(void);
		// increments hits count - equal to "make a hit"
		const Ship* operator++();
		// return the name of the ship
		std::string getName(void);
		// gives and ability to copy pointer to the ship
		bool operator==(const Ship* ship);
		// prints the ship to the given stream
		friend std::ostream& operator<<(std::ostream& os, const Ship* ship);
	};
}

#endif