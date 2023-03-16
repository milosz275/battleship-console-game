#include "Ai.h"

Ai::Ai() : BasePlayer("Computer"), targeted(false), x_prev(-1), y_prev(-1), x_prev_prev(-1), y_prev_prev(-1), x_first(-1), y_first(-1) {}

void Ai::populate_board(void)
{
	std::cout << "populating board of " << PlayerName << std::endl;
	create_boats_populate_auto();
}

bool Ai::move(BasePlayer& opponent)
{
	std::cout << "move of the computer" << std::endl;
	moves++;
	while (combo)
	{
		std::cout << "Computer's board:" << std::endl;
		print_board();
		std::cout << "Your board:" << std::endl;
		opponent.print_board_discreetly();

		//cout << "move of a player" << endl;
		int x = -1;
		int y = -1;

		bool goodCoordinates = false;
		while (!goodCoordinates)
		{
			// coordinates
			if (targeted)
			{
				// second hit
				if (x_prev_prev == -1 && y_prev_prev == -1)
				{
					if (!((*opponent.getBoard())[y_prev + 1][x_prev].check_if_hit()))
					{
						x = x_prev;
						y = y_prev + 1;
					}
					else if (!((*opponent.getBoard())[y_prev - 1][x_prev].check_if_hit()))
					{
						x = x_prev;
						y = y_prev - 1;
					}
					else if (!((*opponent.getBoard())[y_prev][x_prev + 1].check_if_hit()))
					{
						x = x_prev + 1;
						y = y_prev;
					}
					else if (!((*opponent.getBoard())[y_prev][x_prev - 1].check_if_hit()))
					{
						x = x_prev - 1;
						y = y_prev;
					}
					else
						throw Exception("Error while Ai was taking a shot: wrong coordinates of second hit");
				}
				else // above the second hit
				{
					if (x_prev == x_prev_prev)
					{
						if (y_prev > y_prev_prev && !((*opponent.getBoard())[y_prev + 1][x_prev].check_if_hit()))
						{
							x = x_prev;
							y = y_prev + 1;
						}
						else if (y_prev < y_prev_prev && !((*opponent.getBoard())[y_prev - 1][x_prev].check_if_hit()))
						{
							x = x_prev;
							y = y_prev - 1;
						}
						else
							throw Exception("Error while Ai was taking a shot: wrong coordinates of another hit (x_prev == x_prev_prev)");
					}
					else if (y_prev == y_prev_prev)
					{
						if (x_prev > x_prev_prev && !((*opponent.getBoard())[y_prev][x_prev + 1].check_if_hit()))
						{
							x = x_prev + 1;
							y = y_prev;
						}
						else if (x_prev < x_prev_prev && !((*opponent.getBoard())[y_prev][x_prev - 1].check_if_hit()))
						{
							x = x_prev - 1;
							y = y_prev;
						}
						else 
							throw Exception("Error while Ai was taking a shot: wrong coordinates of another hit (y_prev == y_prev_prev)");
					}
					else
						throw Exception("Error while Ai was taking a shot: wrong coordinates above the second hit");
				}
			}
			else // random hit, not targeted
			{
				x = rand() % 10;
				y = rand() % 10;
			}

			
			

			// if the hit flag is already set, repeat giving coordinates proccess
			if (!((*opponent.getBoard())[y][x].check_if_hit()))
				goodCoordinates = true;
		}
		std::cout << "Computer shot at: " << (char)std::toupper((int)coords_inv[x + 1]) << y + 1 << std::endl;

		// sets the hit flag on a target square
		(*opponent.getBoard())[y][x].setHit();

		// check and hit
		if ((*opponent.getBoard())[y][x].check_if_contains_ship())
		{
			std::cout << "hit!" << std::endl;
			Ship* returned_ship = (*opponent.getBoard())[y][x].getShip();
			opponent.hit_ship(returned_ship);
			targeted = true;
			// first hit
			if (x_prev != -1 && y_prev != -1)
			{
				x_prev_prev = x_prev;
				y_prev_prev = y_prev;
				x_first = x;
				y_first = y;
			}
			x_prev = x;
			y_prev = y;

			// sunken ship
			if (returned_ship->getHits() == returned_ship->getSize())
			{
				std::cout << returned_ship->getName() << " was sunken!" << std::endl;
				this->operator++();
				targeted = false;

				x_first = -1;
				y_first = -1;
				x_prev = -1;
				y_prev = -1;
				x_prev_prev = -1;
				y_prev_prev = -1;

				// end of the game
				if (getKills() == 5)
				{
					std::cout << PlayerName << " won!" << std::endl;
					return true;
				}
			}
			combo = true;
			std::cout << PlayerName << " hit a ship and have another move" << std::endl;
		}
		else // miss
		{
			std::cout << "miss!" << std::endl;
			/*if (x_prev_prev != -1 && y_prev_prev != -1) //todo
			{
				x_prev_prev = x_prev;
				y_prev_prev = y_prev;
			}*/
			x_prev = x_first;
			y_prev = y_first;

			// tmp - todo: intelligent change of targeting
			x_prev_prev = -1;
			y_prev_prev = -1;

			combo = false;
			opponent.setCombo();
		}
	}
	return false;
}