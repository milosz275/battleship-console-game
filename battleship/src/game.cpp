#include "include/game.h"

// todo:
// save gamestate
// normal dist for shots
// simulate ai game
// stats in txt

namespace battleship
{
	game::game() : m_finished_game(false), m_player_1(NULL), m_player_2(NULL), m_current_player(NULL) { srand((unsigned)time(NULL)); clear_screen(); welcome_message(); };

	game::~game() { delete m_player_1; delete m_player_2; };

	void game::welcome_message(std::ostream& os) { os << "Welcome to the Battleship game!" << std::endl; }

	void game::create_players(void)
	{
		assert(m_player_1 == NULL && m_player_2 == NULL);

		std::string name;
		m_os << "Give the name of the first player: ";
		std::getline(m_is, name);
		m_player_1 = new player(name);
		m_os << "Do you want to play against another player or a computer? ";
		std::string answer;
		std::getline(m_is, answer);
		transform(answer.begin(), answer.end(), answer.begin(), tolower);

		while (1)
		{
			if (answer == "1" || answer == "player" || answer == "person" || answer == "friend")
			{
				name.erase();
				m_os << "Give the name of the second player: ";
				std::getline(m_is, name);
				m_player_2 = new player(name);
				break;
			}
			else if (answer == "2" || answer == "ai" || answer == "pc" || answer == "computer")
			{
				m_player_2 = new ai();
				break;
			}
			m_os << "Wrong opponent supplied: " << answer << std::endl;
			m_os << "Try again: ";
			std::getline(m_is, answer);
			transform(answer.begin(), answer.end(), answer.begin(), tolower);
		}

		// fill the boards with ship
		m_player_1->populate_board();
		m_player_2->populate_board();

		// add remaining ship to the opponent
		m_player_1->add_ship_to_opponent(*m_player_2);
		m_player_2->add_ship_to_opponent(*m_player_1);

		// create loop
		m_player_1->set_next_player(m_player_2);
		m_player_2->set_next_player(m_player_1);
	}

	void game::load_game(std::string file_name)
	{
		assert(m_player_1 == NULL && m_player_2 == NULL);

		// load file with boards and moves
		std::ifstream file;
		file.open(file_name);
		if (file.fail())
			throw std::runtime_error("File was't opened");

		// todo: initialize players with loaded boards

		// save moves in a list
		std::list<std::string> moves;

		// prepare the game from the saved state
		m_current_player = m_player_1;
		while (!moves.empty() && !m_finished_game)
		{
			m_finished_game = m_current_player->move(*m_current_player->get_next_player(), moves);
			switch_turn();
		}

	}

	void game::switch_turn(void)
	{
		assert(m_player_1 != NULL && m_player_2 != NULL);
		m_current_player = m_current_player->get_next_player();
	}

	void game::clear_screen(void)
	{
		#ifdef WINDOWS
		std::system("cls");

		#else
		// POSIX systems
		std::system("clear");

		#endif
	}

	void game::play(void)
	{
		if (m_player_1 == NULL || m_player_2 == NULL)
		{
			m_os << "Players were not created" << std::endl;
			m_os << "Use create_players or load_game to initiaze the players" << std::endl;
			return;
		}
		if (m_finished_game)
		{
			m_os << "Game is already finished" << std::endl;
			return;
		}

		m_current_player = m_player_1;
		while (!m_finished_game)
		{
			#ifndef _DEBUG
			clear_screen();
			#endif // !_DEBUG

			m_os << "Player move: " << m_current_player->get_name() << std::endl;
			m_finished_game = m_current_player->move(*m_current_player->get_next_player());
			system("pause");
			switch_turn();
		}
	}
}


