#ifndef PLAYER_H
#define PLAYER_H

#include "include/base_player.h"
#include <string>

namespace battleship
{
	class player : public base_player
	{
	public:
		// creates a player of a given name
		player(std::string name);
		// deletes the player
		~player();
		// groups method calls, lets the player decide how to populate board: manually or automatically
		void populate_board(void);
		// lets the player set all the ship manually
		void create_boats_populate_manually(void);
		// sets the given ship on the board
		void fill_board_manually(ship& ship);
		// lets the player make a move
		bool move(base_player& opponent);
	};
}
	
#endif