#ifndef AI_H
#define AI_H

#include "BasePlayer.h"

class Ai : public BasePlayer
	{
	protected:
		// flag indicating if the bot is targeting a ship
		bool targeted;
		// count of hits in current targeting
		int hit_in_firing;
		// x coordinate of previous hit
		int x_prev;
		// y coordinate of previous hit
		int y_prev;
		// x coordinate of second previous hit
		int x_prev_prev;
		// y coordinate of second previous hit
		int y_prev_prev;
		// x coordinate of first hit in given targeting
		int x_first;
		// y coordinate of first hit in given targeting
		int y_first;
		// x coordinate of second hit in given targeting
		int x_second;
		// y coordinate of second hit in given targeting
		int y_second;
		// x coordinate of next scheduled hit in given targeting
		int x_next;
		// y coordinate of next scheduled hit in given targeting
		int y_next;
	public:
		// creates a bot
		Ai();
		// populate board automatically
		void populate_board(void);
		// let the bot make a move on the board
		bool move(BasePlayer& opponent);
	};

#endif