#include "include/player.h"

namespace battleship
{
	player::player(std::string n) : base_player(n) {}

	player::~player() {}

	void player::populate_board(void)
	{
		m_os << "populating board of " << m_player_name << std::endl;
		m_os << "manually or auto? ";
		std::string answer;
		std::getline(m_is, answer);
		transform(answer.begin(), answer.end(), answer.begin(), tolower);
		if (answer == "manually" || answer == "man" || answer == "1")
			create_boats_populate_manually();
		else if (answer == "auto" || answer == "automatical" || answer == "automatically" || answer == "2")
			create_boats_populate_auto();
		else
			throw game_exceptions::exception("Wrong method of populating board supplied: " + answer);

		// todo: add created ship to the opponent's list: ship to sink
	}

	void player::fill_board_manually(ship& ship)
	{
		bool occupied = true;
		int x;
		int y;
		bool horizontal;
		while (occupied)
		{
			print_board();
			m_os << "setting: " << ship.get_name() << "; size: " << ship.get_size() << std::endl;
			m_os << "give the starting x coordinate: ";
			m_is >> x;
			if (x < 1 || x > 10)
				throw game_exceptions::exception("Wrong x coordinate supplied: " + std::to_string(x));
			m_os << "give the starting y coordinate: ";
			m_is >> y;
			if (y < 1 || y > 10)
				throw game_exceptions::exception("Wrong y coordinate supplied: " + std::to_string(y));

			// coordinates translation
			--x, --y;

			// orientation choice
			std::string answer;
			m_os << "should the ship be horizontal or vertical? ";
			m_is >> answer;
			if (answer == "1" || answer == "h" || answer == "hor" || answer == "horizontal" || answer == "horizontally")
				horizontal = true;
			else if (answer == "2" || answer == "v" || answer == "vert" || answer == "vertical" || answer == "horizontally")
				horizontal = false;
			else
				throw game_exceptions::exception("Wrong orientation supplied: " + answer);

			occupied = check_neighbourhood(x, y, ship.get_size(), horizontal);
			if (occupied)
				m_os << "supplied coordinates colide with another ship" << std::endl;
		}
		insert_boat(ship, x, y, horizontal);
	}

	void player::create_boats_populate_manually(void)
	{
		// create ship
		ship Destroyer(2, "Destroyer"),
			Submarine(3, "Submarine"),
			Cruiser(3, "Cruiser"),
			Battleship(4, "Battleship"),
			Carrier(5, "Carrier");
		// set ship according to player's will
		fill_board_manually(Carrier);
		fill_board_manually(Battleship);
		fill_board_manually(Cruiser);
		fill_board_manually(Submarine);
		fill_board_manually(Destroyer);
	}

	bool player::move(base_player& opponent)
	{
		while (m_combo)
		{
			m_os << "Your board:" << std::endl;
			print_board();
			m_os << "Your opponents' board:" << std::endl;
			opponent.print_board_discreetly();

			//cout << "move of a player" << endl;
			int x = -1;
			int y = -1;

			bool goodCoordinates = false;
			while (!goodCoordinates)
			{
				// flush the buffer
				std::cin.clear();
				//std::cin.ignore(INT_MAX);

				// coordinates
				std::string coordinates;
				m_os << "Give coordinates of the shot (ex. A1): ";
				std::getline(m_is, coordinates);
				if (coordinates.size() > 3 || coordinates.size() < 2)
				{
					m_os << "Wrong coordinates length. Try again" << std::endl;
					continue;
				}

				// getting first coordinate
				transform(coordinates.begin(), coordinates.end(), coordinates.begin(), tolower);
				char first_sign = coordinates[0];
				int tmp = coords[first_sign];
				if (tmp < 1 || tmp > 10)
				{
					m_os << "Wrong first coordinates supplied: " << first_sign << std::endl;
					m_os << "Try again" << std::endl;
					continue;
				}
				x = tmp - 1;

				// getting second coordinate
				// todo: repair 10 field. for example A10
				char second_sign = coordinates[1];
				tmp = second_sign - '0';
				if ((coordinates.size() == 3 && second_sign != '1') || (coordinates.size() == 2 && (tmp < 1 || tmp > 10)))
				{
					m_os << "Wrong second coordinates supplied: " << second_sign << coordinates[2] << std::endl;
					m_os << "Try again" << std::endl;
					continue;
				}
				y = tmp - 1;

				// if the hit flag is already set, repeat giving coordinates proccess
				if ((*opponent.get_board())[y][x].check_if_hit())
					m_os << "That coordinates where already shot at. Try again" << std::endl;
				else
					goodCoordinates = true;
			}

			// sets the hit flag on a target square
			(*opponent.get_board())[y][x].set_hit();

			// check and hit
			if ((*opponent.get_board())[y][x].check_if_contains_ship())
			{
				// hit
				m_os << "hit!" << std::endl;
				ship* returned_ship = (*opponent.get_board())[y][x].get_ship();
				opponent.hit_ship(returned_ship);

				// sunken ship
				if (returned_ship->get_hits() == returned_ship->get_size())
				{
					m_os << returned_ship->get_name() << " was sunken!" << std::endl;
					this->operator++();

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
			else
			{
				m_os << "miss!" << std::endl;
				m_combo = false;
				opponent.set_combo();
			}
		}
		return false;
	}
}