#ifndef PLAYER_H
#define PLAYER_H

#include "BasePlayer.h"
#include <string>

class Player : public BasePlayer
	{
	protected:

	public:

		Player(std::string n);

		void populate_board(void);

		void create_boats_populate_manually(void);

		void fill_board_manually(Ship& s);

		bool move(BasePlayer& opponent);
	};
	
#endif