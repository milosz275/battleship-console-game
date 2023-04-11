#include "include/Game.h"
// todo in final version: system("cls") to separate turns

namespace Battleship
{
	Game::Game() : m_finished_game(false), m_player_1(NULL), m_player_2(NULL) { srand((unsigned)time(NULL)); create_players(); };

	Game::~Game() { delete m_player_1, m_player_2; };

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
		if (answer == "player" || answer == "person" || answer == "friend" || answer == "1")
		{
			name.erase();
			std::cout << "give the name of the second player: ";
			std::getline(std::cin, name);
			m_player_2 = new Player(name);
		}
		else if (answer == "ai" || answer == "pc" || answer == "computer" || answer == "2")
			m_player_2 = new Ai();
		else
			throw GameExceptions::Exception("Wrong opponent supplied: " + answer);

		m_player_1->populate_board();
		m_player_2->populate_board();
	}

	void Game::play(void)
	{
		if (m_player_1 == NULL || m_player_2 == NULL)
			throw GameExceptions::Exception("Players were not created");

		m_player_1->print_board();
		m_player_2->print_board();

		m_player_1->print_ship();
		m_player_2->print_ship();

		while (!m_finished_game)
		{
			std::cout << "player 1 move" << std::endl;
			m_finished_game = m_player_1->move(*m_player_2);

			if (m_finished_game)
				break;

			std::cout << "player 2 move" << std::endl;
			m_finished_game = m_player_2->move(*m_player_1);
		}
	}
}


