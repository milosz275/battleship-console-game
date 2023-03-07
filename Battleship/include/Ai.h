#ifndef AI_H
#define AI_H

#include "BasePlayer.h"

class Ai : public BasePlayer
	{
	protected:

	public:

		Ai();

		void populate_board(void);

		bool move(BasePlayer& opponent);
	};

#endif