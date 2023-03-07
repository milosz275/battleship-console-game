#include "Ai.h"

Ai::Ai() : BasePlayer("Computer") {}

void Ai::populate_board(void)
{
	std::cout << "populating board of " << PlayerName << std::endl;
	create_boats_populate_auto();
}

bool Ai::move(BasePlayer& opponent)
{
	std::cout << "move of a computer" << std::endl;
	return false;
}