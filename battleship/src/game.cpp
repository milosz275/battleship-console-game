#include "include/Game.h"
// todo: save gamestate

namespace Battleship
{
	Game::Game() : m_finished_game(false), m_player_1(NULL), m_player_2(NULL), m_current_player(NULL) { srand((unsigned)time(NULL)); clear_screen(); welcome_message(); create_players(); };

	Game::~Game() { delete m_player_1, m_player_2; };

	void Game::welcome_message(void) { std::cout << "Welcome to the Battleship game!" << std::endl; }

	void Game::create_players(void)
	{
		std::string name;
		std::cout << "give the name of the first player: ";
		std::getline(std::cin, name);
		m_player_1 = new Player(name);
		std::cout << "Do you want to play against another player or a computer? ";
		std::string answer;
		std::getline(std::cin, answer);
		transform(answer.begin(), answer.end(), answer.begin(), tolower);

		while (1)
		{
			if (answer == "1" || answer == "player" || answer == "person" || answer == "friend")
			{
				name.erase();
				std::cout << "give the name of the second player: ";
				std::getline(std::cin, name);
				m_player_2 = new Player(name);
				break;
			}
			else if (answer == "2" || answer == "ai" || answer == "pc" || answer == "computer")
			{
				m_player_2 = new Ai();
				break;
			}
			std::cout << "Wrong opponent supplied: " << answer << std::endl;
			std::cout << "Try again: ";
			std::getline(std::cin, answer);
			transform(answer.begin(), answer.end(), answer.begin(), tolower);
		}

		// fill the boards with ship
		m_player_1->populate_board();
		m_player_2->populate_board();

		// create loop
		m_player_1->set_next_player(m_player_2);
		m_player_2->set_next_player(m_player_1);
	}

	void Game::switch_turn(void)
	{
		assert(m_player_1 != NULL && m_player_2 != NULL);
		m_current_player = m_current_player->get_next_player();
	}

	void Game::clear_screen(void)
	{
		#ifdef WINDOWS
		std::system("cls");

		#else
		// POSIX systems
		std::system("clear");

		#endif
	}

	void Game::play(void)
	{
		if (m_player_1 == NULL || m_player_2 == NULL)
		{
			std::cout << "Players were not created" << std::endl;
			return;
		}

		m_current_player = m_player_1;
		while (!m_finished_game)
		{
			clear_screen();
			std::cout << "Player move: " << m_current_player->get_name() << std::endl;
			m_finished_game = m_current_player->move(*m_current_player->get_next_player());
			std::cout << "Press enter to continue: ";
			int tmp = getchar();
			switch_turn();
		}
	}
}


