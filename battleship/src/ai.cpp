#include "include/ai.h"

namespace battleship
{
	ai::ai() : base_player("Computer"), m_targeted(false), m_x_prev(-1), m_y_prev(-1), m_x_first(-1), m_y_first(-1), m_x_second(-1), m_y_second(-1),
		m_hit_in_firing(0), m_all_moves(0), m_moves(0) {}

	ai::~ai() {}

	void ai::populate_board(void)
	{
		m_os << "populating board of " << m_player_name << std::endl;
		create_boats_populate_auto();
	}

	bool ai::move(base_player& opponent)
	{
		while (m_combo)
		{
			m_all_moves++;

			//cout << "move of a player" << endl;
			int x = -1;
			int y = -1;

			bool good_coordinates = false;
			while (!good_coordinates)
			{
				// when target ship is being fired at
				if (m_targeted)
				{
					if (m_hit_in_firing == 1) // first was hit, now hitting second
					{
						if (!(m_y_first + 1 >= 10) && !((*opponent.get_board())[m_y_first + 1][m_x_first].check_if_hit()))
						{
							x = m_x_first;
							y = m_y_first + 1;
						}
						else if (!(m_y_first - 1 <= -1) && !((*opponent.get_board())[m_y_first - 1][m_x_first].check_if_hit()))
						{
							x = m_x_first;
							y = m_y_first - 1;
						}
						else if (!(m_x_first + 1 >= 10) && !((*opponent.get_board())[m_y_first][m_x_first + 1].check_if_hit()))
						{
							x = m_x_first + 1;
							y = m_y_first;
						}
						else if (!(m_x_first - 1 <= -1) && !((*opponent.get_board())[m_y_first][m_x_first - 1].check_if_hit()))
						{
							x = m_x_first - 1;
							y = m_y_first;
						}
						else
							throw game_exceptions::exception("ai targeting error");
					}
					else if (m_hit_in_firing == 2) // second was hit, now hitting third
					{
						if (m_x_first == m_x_second) // vertically
						{
							bool found = false;
							if (m_y_second > m_y_first)
							{
								if (!(m_y_second + 1 >= m_board_size) && !((*opponent.get_board())[m_y_second + 1][m_x_first].check_if_hit()))
								{
									found = true;
									x = m_x_first;
									y = m_y_second + 1;
								}
							}
							else
							{
								if (m_y_second - 1 >= 0 && !((*opponent.get_board())[m_y_second - 1][m_x_first].check_if_hit()))
								{
									found = true;
									x = m_x_first;
									y = m_y_second - 1;
								}
							}
							if (!found)
							{
								if (m_y_first - 1 >= 0 && !((*opponent.get_board())[m_y_first - 1][m_x_first].check_if_hit()))
								{
									x = m_x_first;
									y = m_y_first - 1;
								}
								else
									throw game_exceptions::exception("ai targeting error");
							}
						}
						else if (m_y_first == m_y_second) // horizontally
						{
							bool found = false;
							if (m_x_second > m_x_first)
							{
								if (!(m_x_second + 1 >= m_board_size) && !((*opponent.get_board())[m_y_first][m_x_second + 1].check_if_hit()))
								{
									found = true;
									x = m_x_second + 1;
									y = m_y_first;
								}
							}
							else
							{
								if (m_x_second - 1 >= 0 && !((*opponent.get_board())[m_y_first][m_x_second - 1].check_if_hit()))
								{
									found = true;
									x = m_x_second - 1;
									y = m_y_first;
								}
							}
							if (!found)
							{
								if (m_x_first - 1 >= 0 && !((*opponent.get_board())[m_y_first][m_x_first - 1].check_if_hit()))
								{
									x = m_x_first - 1;
									y = m_y_first;
								}
								else
									throw game_exceptions::exception("ai targeting error");
							}
						}
						else
							throw game_exceptions::exception("ai targeting error");
					}
					else if (m_hit_in_firing >= 3)
					{
						if (m_x_first == m_x_second) // vertically
						{
							bool found = false;
							if (m_y_second > m_y_first)
							{
								if (m_y_prev > m_y_second)
								{
									if (!(m_y_prev + 1 >= m_board_size) && !((*opponent.get_board())[m_y_prev + 1][m_x_first].check_if_hit()))
									{
										found = true;
										x = m_x_first;
										y = m_y_prev + 1;
									}
									else if (m_y_first - 1 >= 0 && !((*opponent.get_board())[m_y_first - 1][m_x_first].check_if_hit()))
									{
										found = true;
										x = m_x_first;
										y = m_y_first - 1;
									}
									else
										throw game_exceptions::exception("ai targeting error");
								}
								else // m_y_prev < m_y_second (has changed direction)
								{
									if (m_y_prev - 1 >= 0 && !((*opponent.get_board())[m_y_prev - 1][m_x_first].check_if_hit()))
									{
										found = true;
										x = m_x_first;
										y = m_y_prev - 1;
									}
									else
										throw game_exceptions::exception("ai targeting error");
								}
							}
							else // m_y_second < m_y_first (downwards)
							{
								if (m_y_prev < m_y_second)
								{
									if (m_y_prev - 1 >= 0 && !((*opponent.get_board())[m_y_prev - 1][m_x_first].check_if_hit()))
									{
										found = true;
										x = m_x_first;
										y = m_y_prev - 1;
									}
									else if (!(m_y_first + 1 >= m_board_size) && !((*opponent.get_board())[m_y_first + 1][m_x_first].check_if_hit()))
									{
										found = true;
										x = m_x_first;
										y = m_y_first + 1;
									}
									else
										throw game_exceptions::exception("ai targeting error");
								}
								else // m_y_prev > m_y_second (has changed direction)
								{
									if (m_y_prev + 1 >= 0 && !((*opponent.get_board())[m_y_prev + 1][m_x_first].check_if_hit()))
									{
										found = true;
										x = m_x_first;
										y = m_y_prev + 1;
									}
									else
										throw game_exceptions::exception("ai targeting error");
								}

								if (m_y_second - 1 >= 0 && !((*opponent.get_board())[m_y_second - 1][m_x_first].check_if_hit()))
								{
									found = true;
									x = m_x_first;
									y = m_y_second - 1;
								}
							}
						}
						else if (m_y_first == m_y_second) // horizontally
						{
							bool found = false;
							if (m_x_second > m_x_first)
							{
								if (m_x_prev > m_x_second)
								{
									if (!(m_x_prev + 1 >= m_board_size) && !((*opponent.get_board())[m_y_first][m_x_prev + 1].check_if_hit()))
									{
										found = true;
										x = m_x_prev + 1;
										y = m_y_first;
									}
									else if (m_x_first - 1 >= 0 && !((*opponent.get_board())[m_y_first][m_x_first - 1].check_if_hit()))
									{
										found = true;
										x = m_x_first - 1;
										y = m_y_first;
									}
									else
										throw game_exceptions::exception("ai targeting error");
								}
								else // m_y_prev < m_y_second (has changed direction)
								{
									if (m_x_prev - 1 >= 0 && !((*opponent.get_board())[m_y_first][m_x_prev - 1].check_if_hit()))
									{
										found = true;
										x = m_x_prev - 1;
										y = m_y_first;
									}
									else
										throw game_exceptions::exception("ai targeting error");
								}
							}
							else // m_x_second < m_x_first (downwards)
							{
								if (m_x_prev < m_x_second)
								{
									if (m_x_prev - 1 >= 0 && !((*opponent.get_board())[m_y_first][m_x_prev - 1].check_if_hit()))
									{
										found = true;
										x = m_x_prev - 1;
										y = m_y_first;
									}
									else if (!(m_x_first + 1 >= m_board_size) && !((*opponent.get_board())[m_y_first][m_x_first + 1].check_if_hit()))
									{
										found = true;
										x = m_x_first + 1;
										y = m_y_first;
									}
									else
										throw game_exceptions::exception("ai targeting error");
								}
								else // m_y_prev > m_y_second (has changed direction)
								{
									if (m_x_prev + 1 >= 0 && !((*opponent.get_board())[m_y_first][m_x_prev + 1].check_if_hit()))
									{
										found = true;
										x = m_x_prev + 1;
										y = m_y_first;
									}
									else
										throw game_exceptions::exception("ai targeting error");
								}

								if (m_x_second - 1 >= 0 && !((*opponent.get_board())[m_y_first][m_x_second - 1].check_if_hit()))
								{
									found = true;
									x = m_x_second - 1;
									y = m_y_first;
								}
							}
						}
						else
							throw game_exceptions::exception("ai targeting error");
					}
					else // hit in firing > 2
						throw game_exceptions::exception("ai targeting error");
				}
				else // random hit, ai doesn't know where ship are
				{
					m_moves++;

					// todo: smallest alive ship targeting !!!
					x = rand() % 10;
					y = rand() % 10;
				}
				// make sure chosen coords are valid
				assert(x >= 0 && x < 10 && y >= 0 && y < 10);

				// if the hit flag is already set, repeat giving coordinates proccess
				if (!((*opponent.get_board())[y][x].check_if_hit()))
					good_coordinates = true;
			}
			m_os << "Computer shot at: " << (char)std::toupper((int)coords_inv[x + 1]) << y + 1 << std::endl;

			// sets the hit flag on a target square
			(*opponent.get_board())[y][x].set_hit();

			// check and hit
			if ((*opponent.get_board())[y][x].check_if_contains_ship())
			{
				m_os << "hit!" << std::endl;
				ship* returned_ship = (*opponent.get_board())[y][x].get_ship();
				opponent.hit_ship(returned_ship);
				m_targeted = true;
				m_hit_in_firing++;
				// todo: dynamic ship recognition

				if (m_hit_in_firing == 1)
				{
					m_x_first = x;
					m_y_first = y;
				}
				else if (m_hit_in_firing == 2)
				{
					m_x_second = x;
					m_y_second = y;
				}
				else // 3, 4, 5...
				{
					m_x_prev = x;
					m_y_prev = y;
				}

				// sunken ship
				if (returned_ship->get_hits() == returned_ship->get_size())
				{
					m_os << returned_ship->get_name() << " was sunken!" << std::endl;
					this->operator++();
					m_targeted = false;
					m_hit_in_firing = 0;

					// todo: save sunken ship for better hit chance
					m_x_first = -1;
					m_y_first = -1;
					m_x_second = -1;
					m_y_second = -1;
					m_x_prev = -1;
					m_y_prev = -1;

					// end of the game
					if (get_kills() == 5)
					{
						m_os << m_player_name << " won!" << std::endl;
						return true;
					}
				}
				m_combo = true;
				m_os << m_player_name << " hit a ship and have another move" << std::endl;
			}
			else // miss
			{
				m_os << "miss!" << std::endl;
				m_combo = false;
				opponent.set_combo();
			}
		}

		// print the boards
		m_os << "Computer's board:" << std::endl;
		print_board_discreetly();
		m_os << "Your board:" << std::endl;
		opponent.print_board();

		return false;
	}
}