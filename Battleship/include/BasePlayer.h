#ifndef BASEPLAYER_H
#define BASEPLAYER_H

#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <cassert>
#include "include/Exception.h"
#include "include/Square.h"
#include "include/Ship.h"

namespace Battleship
{
	static std::map<char, int> coords{ {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}, {'f', 6}, {'g', 7}, {'h', 8}, {'i', 9}, {'j', 10} };
	static std::map<int, char> coords_inv{ {1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}, {6, 'f'}, {7, 'g'}, {8, 'h'}, {9, 'i'}, {10, 'j'} };

	class BasePlayer
	{
	protected:
		// size of the board: number of rows and columns
		const int m_board_size = 10;
		// board belonging to the player
		std::vector<std::vector<Square>>* m_board;
		// name of the player
		std::string m_player_name;
		// indicates if a player has a right to strike multiple times. start with true to allow the first move
		bool m_combo;
		// counts sunken ships of an opponent
		int m_kills;
		// list of own ship
		std::list<Ship*>* m_ship_list;
		// moves count, may be used to evaluate ai's efficiency
		int m_moves;
	private:
		// allocates the board
		void create_board(void);
	public:
		// creates a base class of a player: Player or Ai
		BasePlayer(std::string player_name);
		// deletes a player
		virtual ~BasePlayer();
		// populate board automatically or manually, has to be overloaded in derived classes
		virtual void populate_board(void) = 0;
		// returns true, if the last ship was sunken
		virtual bool move(BasePlayer& opponent) = 0;
		// returns kill count
		int get_kills(void);
		// sets the combo flag to allow making a move
		void set_combo(void);
		// increments kills count
		const BasePlayer& operator++();
		// returns the board
		std::vector<std::vector<Square>>* get_board(void);
		// check given coordinates, if the ship can be placed there
		bool check_neighbourhood(int x, int y, int length, bool horizontally);
		// inserts a boat at given coordinates
		void insert_boat(Ship& s, int x, int y, bool horizontally);
		// randomly generates coordinates, checks the neighbourhood and inserts given ship
		void fill_board_auto(Ship& s);
		// generates all ship, populates the board with them automatically
		void create_boats_populate_auto(void);
		// prints the board to given stream
		void print_board(std::ostream& os = std::cout);
		// prints the board to given stream
		void print_board_discreetly(std::ostream& os = std::cout);
		// prints a ship list
		void print_ship(std::ostream& os = std::cout);
		// hits a ship
		void hit_ship(Ship* s);
	};
}

#endif