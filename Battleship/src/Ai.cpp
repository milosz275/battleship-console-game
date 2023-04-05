#include "include/Ai.h"

namespace Battleship
{
	Ai::Ai() : BasePlayer("Computer"), targeted(false), x_prev(-1), y_prev(-1), x_first(-1), y_first(-1), x_second(-1), y_second(-1), hit_in_firing(0) {}

	Ai::~Ai() {}

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
					if (hit_in_firing == 1) // first was hit, now hitting second
					{
						if (!(y_first + 1 >= 10) && !((*opponent.getBoard())[y_first + 1][x_first].check_if_hit()))
						{
							x = x_first;
							y = y_first + 1;
						}
						else if (!(y_first - 1 <= -1) && !((*opponent.getBoard())[y_first - 1][x_first].check_if_hit()))
						{
							x = x_first;
							y = y_first - 1;
						}
						else if (!(x_first + 1 >= 10) && !((*opponent.getBoard())[y_first][x_first + 1].check_if_hit()))
						{
							x = x_first + 1;
							y = y_first;
						}
						else if (!(x_first - 1 <= -1) && !((*opponent.getBoard())[y_first][x_first - 1].check_if_hit()))
						{
							x = x_first - 1;
							y = y_first;
						}
						else
							throw GameExceptions::Exception("Targeting error");
					}
					else if (hit_in_firing == 2) // second was hit, now hitting third
					{
						if (x_first == x_second) // vertically
						{
							bool found = false;
							if (y_second > y_first)
							{
								if (!(y_second + 1 >= board_size) && !((*opponent.getBoard())[y_second + 1][x_first].check_if_hit()))
								{
									found = true;
									x = x_first;
									y = y_second + 1;
								}
							}
							else
							{
								if (y_second - 1 >= 0 && !((*opponent.getBoard())[y_second - 1][x_first].check_if_hit()))
								{
									found = true;
									x = x_first;
									y = y_second - 1;
								}
							}
							if (!found)
							{
								if (y_first - 1 >= 0 && !((*opponent.getBoard())[y_first - 1][x_first].check_if_hit()))
								{
									x = x_first;
									y = y_first - 1;
								}
								else
									throw GameExceptions::Exception("Targeting error");
							}
						}
						else if (y_first == y_second) // horizontally
						{
							bool found = false;
							if (x_second > x_first)
							{
								if (!(x_second + 1 >= board_size) && !((*opponent.getBoard())[y_first][x_second + 1].check_if_hit()))
								{
									found = true;
									x = x_second + 1;
									y = y_first;
								}
							}
							else
							{
								if (x_second - 1 >= 0 && !((*opponent.getBoard())[y_first][x_second - 1].check_if_hit()))
								{
									found = true;
									x = x_second - 1;
									y = y_first;
								}
							}
							if (!found)
							{
								if (x_first - 1 >= 0 && !((*opponent.getBoard())[y_first][x_first - 1].check_if_hit()))
								{
									x = x_first - 1;
									y = y_first;
								}
								else
									throw GameExceptions::Exception("Targeting error");
							}
						}
						else
							throw GameExceptions::Exception("Targeting error");
					}
					else if (hit_in_firing >= 3)
					{
						if (x_first == x_second) // vertically
						{
							bool found = false;
							if (y_second > y_first)
							{
								if (y_prev > y_second)
								{
									if (!(y_prev + 1 >= board_size) && !((*opponent.getBoard())[y_prev + 1][x_first].check_if_hit()))
									{
										found = true;
										x = x_first;
										y = y_prev + 1;
									}
									else if (y_first - 1 >= 0 && !((*opponent.getBoard())[y_first - 1][x_first].check_if_hit()))
									{
										found = true;
										x = x_first;
										y = y_first - 1;
									}
									else
										throw GameExceptions::Exception("Targeting error");
								}
								else // y_prev < y_second (has changed direction)
								{
									if (y_prev - 1 >= 0 && !((*opponent.getBoard())[y_prev - 1][x_first].check_if_hit()))
									{
										found = true;
										x = x_first;
										y = y_prev - 1;
									}
									else
										throw GameExceptions::Exception("Targeting error");
								}
							}
							else // y_second < y_first (downwards)
							{
								if (y_prev < y_second)
								{
									if (y_prev - 1 >= 0 && !((*opponent.getBoard())[y_prev - 1][x_first].check_if_hit()))
									{
										found = true;
										x = x_first;
										y = y_prev - 1;
									}
									else if (!(y_first + 1 >= board_size) && !((*opponent.getBoard())[y_first + 1][x_first].check_if_hit()))
									{
										found = true;
										x = x_first;
										y = y_first + 1;
									}
									else
										throw GameExceptions::Exception("Targeting error");
								}
								else // y_prev > y_second (has changed direction)
								{
									if (y_prev + 1 >= 0 && !((*opponent.getBoard())[y_prev + 1][x_first].check_if_hit()))
									{
										found = true;
										x = x_first;
										y = y_prev + 1;
									}
									else
										throw GameExceptions::Exception("Targeting error");
								}

								if (y_second - 1 >= 0 && !((*opponent.getBoard())[y_second - 1][x_first].check_if_hit()))
								{
									found = true;
									x = x_first;
									y = y_second - 1;
								}
							}
						}
						else if (y_first == y_second) // horizontally
						{
							bool found = false;
							if (x_second > x_first)
							{
								if (x_prev > x_second)
								{
									if (!(x_prev + 1 >= board_size) && !((*opponent.getBoard())[y_first][x_prev + 1].check_if_hit()))
									{
										found = true;
										x = x_prev + 1;
										y = y_first;
									}
									else if (x_first - 1 >= 0 && !((*opponent.getBoard())[y_first][x_first - 1].check_if_hit()))
									{
										found = true;
										x = x_first - 1;
										y = y_first;
									}
									else
										throw GameExceptions::Exception("Targeting error");
								}
								else // y_prev < y_second (has changed direction)
								{
									if (x_prev - 1 >= 0 && !((*opponent.getBoard())[y_first][x_prev - 1].check_if_hit()))
									{
										found = true;
										x = x_prev - 1;
										y = y_first;
									}
									else
										throw GameExceptions::Exception("Targeting error");
								}
							}
							else // x_second < x_first (downwards)
							{
								if (x_prev < x_second)
								{
									if (x_prev - 1 >= 0 && !((*opponent.getBoard())[y_first][x_prev - 1].check_if_hit()))
									{
										found = true;
										x = x_prev - 1;
										y = y_first;
									}
									else if (!(x_first + 1 >= board_size) && !((*opponent.getBoard())[y_first][x_first + 1].check_if_hit()))
									{
										found = true;
										x = x_first + 1;
										y = y_first;
									}
									else
										throw GameExceptions::Exception("Targeting error");
								}
								else // y_prev > y_second (has changed direction)
								{
									if (x_prev + 1 >= 0 && !((*opponent.getBoard())[y_first][x_prev + 1].check_if_hit()))
									{
										found = true;
										x = x_prev + 1;
										y = y_first;
									}
									else
										throw GameExceptions::Exception("Targeting error");
								}

								if (x_second - 1 >= 0 && !((*opponent.getBoard())[y_first][x_second - 1].check_if_hit()))
								{
									found = true;
									x = x_second - 1;
									y = y_first;
								}
							}
						}
						else
							throw GameExceptions::Exception("Targeting error");
					}
					else // hit in firing > 2
						throw GameExceptions::Exception("Targeting error");
				}
				else // random hit, not targeted
				{
					// todo: smallest alive ship targeting
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
				hit_in_firing++;
				// todo: dynamic ship recognition

				if (hit_in_firing == 1)
				{
					x_first = x;
					y_first = y;
				}
				else if (hit_in_firing == 2)
				{
					x_second = x;
					y_second = y;
				}
				else // 3, 4, 5...
				{
					x_prev = x;
					y_prev = y;
				}

				// sunken ship
				if (returned_ship->getHits() == returned_ship->getSize())
				{
					std::cout << returned_ship->getName() << " was sunken!" << std::endl;
					this->operator++();
					targeted = false;
					hit_in_firing = 0;

					// todo: save sunken ship for better hit chance
					x_first = -1;
					y_first = -1;
					x_second = -1;
					y_second = -1;
					x_prev = -1;
					y_prev = -1;

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
				combo = false;
				opponent.setCombo();
			}
		}
		return false;
	}
}