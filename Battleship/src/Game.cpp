#include "include/Game.h"
// todo in final version: system("cls") to separate turns

namespace Battleship
{
	Game::Game() : finishedGame(false), player_1(NULL), player_2(NULL) { srand((unsigned)time(NULL)); create_players(); };

	Game::~Game() { delete player_1, player_2; };

	void Game::create_players(void)
	{
		std::string name;
		std::cout << "give the name of the first player: ";
		std::getline(std::cin, name);
		player_1 = new Player(name);
		std::cout << "Do you want to play against another player or a computer? ";
		std::string answer;
		std::getline(std::cin, answer);
		transform(answer.begin(), answer.end(), answer.begin(), tolower);
		if (answer == "player" || answer == "person" || answer == "friend" || answer == "1")
		{
			name.erase();
			std::cout << "give the name of the second player: ";
			std::getline(std::cin, name);
			player_2 = new Player(name);
		}
		else if (answer == "ai" || answer == "pc" || answer == "computer" || answer == "2")
			player_2 = new Ai();
		else
			throw Exception("Wrong opponent supplied: " + answer);

		player_1->populate_board();
		player_2->populate_board();
	}

	void Game::play(void)
	{
		if (player_1 == NULL || player_2 == NULL)
			throw Exception("Players were not created");

		player_1->print_board();
		player_2->print_board();

		player_1->print_ship();
		player_2->print_ship();

		while (!finishedGame)
		{
			std::cout << "player 1 move" << std::endl;
			finishedGame = player_1->move(*player_2);

			if (finishedGame)
				break;

			std::cout << "player 2 move" << std::endl;
			finishedGame = player_2->move(*player_1);
		}
	}
}


