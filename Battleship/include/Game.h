#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <list>
#include <map>
#include "Exception.h"
#include "BasePlayer.h"
#include "Player.h"
#include "Ai.h"

namespace Battleship
{
	class Game
	{
		// flag indicating if the game is finished
		bool finishedGame;
		// pointer to the first player
		BasePlayer* player_1;
		// pointer to the second player
		BasePlayer* player_2;
	public:
		// creates game, calls the create_players method
		Game();
		// deletes players
		~Game();
		// creates players and populates boards belonging to the players
		void create_players(void);
		// main game loop
		void play(void);
	};
}

#endif