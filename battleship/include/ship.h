#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <string>
#include <cassert>

namespace battleship
{
	class ship
	{
		// size of the ship
		int m_size;
		// hits count
		int m_hits;
		// name of the ship
		std::string m_name;
	public:
		// creates a ship of a given size and name
		ship(int size, std::string name);
		// returns size of the ship
		int get_size(void);
		// returns hits count
		int get_hits(void);
		// increments hits count - equal to "make a hit"
		const ship* operator++();
		// return the name of the ship
		std::string get_name(void);
		// gives and ability to copy pointer to the ship
		bool operator==(const ship* ship);
		// prints the ship to the given stream
		friend std::ostream& operator<<(std::ostream& os, const ship* ship);
	};
}

#endif