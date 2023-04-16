#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <list>
#include <map>
#include <fstream>
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
		// pointer to the player making move at the moment
		base_player* m_current_player;
		// default output stream
		std::ostream& m_os = std::cout;
		// default input stream
		std::istream& m_is = std::cin;
	public:
		// creates game, calls the create_players method
		game();
		// deletes players
		~game();
		// prints welcome message
		void welcome_message(std::ostream& os = std::cout);
		// switches the flag indicating player's turn
		void switch_turn(void);
		// creates players and populates boards belonging to the players
		void create_players(void);
		// loads the game from file of given name
		void load_game(std::string file_name);
		// clears the screen accordingly to operating system
		void clear_screen(void);
		// main game loop
		void play(void);
	};
}

#endif