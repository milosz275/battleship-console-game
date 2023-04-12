#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <list>
#include <map>
#include "include/exception.h"
#include "include/base_player.h"
#include "include/player.h"
#include "include/ai.h"

namespace battleship
{
	class game
	{
		// flag indicating if the game is finished
		bool m_finished_game;
		// pointer to the first player
		base_player* m_player_1;
		// pointer to the second player
		base_player* m_player_2;
		// 
		base_player* m_current_player;
	public:
		// creates game, calls the create_players method
		game();
		// deletes players
		~game();
		//
		void welcome_message(void);
		// creates players and populates boards belonging to the players
		void create_players(void);
		//
		void switch_turn(void);
		//
		void clear_screen(void);
		// main game loop
		void play(void);
	};
}

#endif