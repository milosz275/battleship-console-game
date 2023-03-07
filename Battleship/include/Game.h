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

		bool finishedGame;

		BasePlayer* player_1;

		BasePlayer* player_2;
	public:

		Game();

		~Game();

		void create_players(void);

		void play(void);
	};
}

#endif