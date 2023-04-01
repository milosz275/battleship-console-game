#ifndef PLAYER_H
#define PLAYER_H

#include "include/BasePlayer.h"
#include <string>

class Player : public BasePlayer
{
public:
	// creates a player of a given name
	Player(std::string n);
	// deletes the player
	~Player();
	// groups method calls, lets the player decide how to populate board: manually or automatically
	void populate_board(void);
	// lets the player set all the ship manually
	void create_boats_populate_manually(void);
	// sets the given ship on the board
	void fill_board_manually(Ship& s);
	// lets the player make a move
	bool move(BasePlayer& opponent);
};
	
#endif