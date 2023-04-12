#ifndef AI_H
#define AI_H

#include "include/base_player.h"
#include <cassert>
// todo:
// heatmap of shots
// checkerboard searching appropriately to smallest ship alive
// normal distribution

namespace battleship
{
	class ai : public base_player
	{
	protected:
		// flag indicating if the bot is targeting a ship
		bool m_targeted;
		// count of hits in current targeting
		int m_hit_in_firing;
		// moves count, used to evaluate ai's efficiency - only before targeting
		int m_moves;
		// moves count, used to evaluate ai's efficiency - all
		int m_all_moves;
		// x coordinate of previous hit
		int m_x_prev;
		// y coordinate of previous hit
		int m_y_prev;
		// x coordinate of first hit in given targeting
		int m_x_first;
		// y coordinate of first hit in given targeting
		int m_y_first;
		// x coordinate of second hit in given targeting
		int m_x_second;
		// y coordinate of second hit in given targeting
		int m_y_second;
	public:
		// creates a bot
		ai();
		// deletes the bot
		~ai();
		// populate board automatically
		void populate_board(void);
		// let the bot make a move on the board
		bool move(base_player& opponent);
	};
}

#endif