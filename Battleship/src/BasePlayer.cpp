#include "BasePlayer.h"

// coordinates are switched due to vector of vectors characteristics
// todo: rotate board

BasePlayer::BasePlayer(std::string n) : board(NULL), PlayerName(n), combo(true), kills(0), ShipList(NULL), moves(0) { create_board(); }

void BasePlayer::create_board(void)
{
	if (board == NULL)
		board = new std::vector<std::vector<Square>>(board_size, std::vector<Square>(board_size));
	else
		throw Exception("Attempted to overwrite the board"); };

void BasePlayer::print_board(std::ostream& os) // todo: iomanip
{
	if (board == NULL)
		throw Exception("Board is empty");
	os << "\t ";
	for (char c = 'A'; c < 'A' + board_size; ++c)
		os << c << "  ";
	for_each(board->begin(), board->end(), [&os, j = 0](std::vector<Square>& v) mutable
		{
			os << std::endl << ++j << " \t|";
			copy(v.begin(), v.end(), std::ostream_iterator<Square>(os, " |"));
		});
	os << std::endl;
}

void BasePlayer::print_board_discreetly(std::ostream& os) // todo: iomanip
{
	if (board == NULL)
		throw Exception("Board is empty");
	os << "\t ";
	for (char c = 'A'; c < 'A' + board_size; ++c)
		os << c << "  ";
	for_each(board->begin(), board->end(), [&os, j = 0](std::vector<Square>& v) mutable
		{
			os << std::endl << ++j << "\t|";
			for_each(v.begin(), v.end(), [&os](Square& s)
				{
					if (s.check_if_hit() && s.check_if_contains_ship())
						os << "X";
					else if (s.check_if_hit())
						os << "/";
					else
						os << "-"; os << " |";
				});
			
		});
	os << std::endl;
}

int BasePlayer::getKills(void) { return kills; }

void BasePlayer::setCombo(void) { combo = true; }

const BasePlayer& BasePlayer::operator++() { kills++; return *this; }

std::vector<std::vector<Square>>* BasePlayer::getBoard(void) { return board; }

void BasePlayer::print_ship(std::ostream& os)
{
	if (ShipList == NULL)
		throw Exception("Ship list is empty");
	copy(ShipList->begin(), ShipList->end(), std::ostream_iterator<Ship*>(os << "shiplist" << std::endl << " |", " |"));
	std::cout << std::endl;
}

void BasePlayer::hit_ship(Ship* s)
{
	for_each(ShipList->begin(), ShipList->end(), [&s](Ship* c) { if (c == s) { (*c).operator++(); }});
}

bool BasePlayer::check_neighbourhood(int x, int y, int length, bool horizontally)
{
	bool occupied = false;

	// actual x coordinates of the test
	int x_start = x, x_end = x;
	// actual y coordinates of the test
	int y_start = y, y_end = y;

	// change coordinates to indexes
	if (horizontally)
		x_end += length - 1;
	else
		y_end += length - 1;

	if (x_start > 0)
		x_start--;
	if (x_end < 9)
		x_end++;
	if (y_start > 0)
		y_start--;
	if (y_end < 9)
		y_end++;

	// check if the coordinates are occupied with a ship (change to all of)
	for_each(board->begin() + y_start, board->begin() + y_end + 1, [&x_start, &x_end, &occupied](std::vector<Square>& v) { for_each(v.begin() + x_start, v.begin() + x_end + 1, [&occupied](Square& sq) { if (sq.check_if_contains_ship()) occupied = true; }); });

	return occupied;
}

void BasePlayer::insert_boat(Ship& s, int x, int y, bool horizontally)
{
	if (horizontally)
		for_each(board->begin() + y, board->begin() + y + 1, [&x, &s, &y](std::vector<Square>& v) { for_each(v.begin() + x, v.begin() + x + s.getSize(), [&s](Square& sq) { sq.setShip(s); }); });
	else
		std::for_each(board->begin() + y, board->begin() + y + s.getSize(), [&x, &s](std::vector<Square>& v) { v[x].setShip(s); });
}

void BasePlayer::fill_board_auto(Ship& s)
{
	bool occupied = true;
	int x = -1;
	int y = -1;
	bool horizontal;
	int size = s.getSize();
	while (occupied)
	{
		horizontal = rand() % 2;
		if (horizontal)
		{
			while (x < 0 || x + size > 9)
				x = rand() % 10;
			y = rand() % 10;
		}
		else
		{
			while (y < 0 || y + size > 9)
				y = rand() % 10;
			x = rand() % 10;
		}
		occupied = check_neighbourhood(x, y, s.getSize(), horizontal);
	}
	insert_boat(s, x, y, horizontal);
}

void BasePlayer::create_boats_populate_auto(void)
{
	ShipList = new std::list<Ship*>;
	Ship* Destroyer = new Ship(2, "Destroyer"), * Submarine = new Ship(3, "Submarine"), * Cruiser = new Ship(3, "Cruiser"), * Battleship = new Ship(4, "Battleship"), * Carrier = new Ship(5, "Carrier");
	ShipList->push_back(Destroyer); ShipList->push_back(Submarine); ShipList->push_back(Cruiser); ShipList->push_back(Battleship), ShipList->push_back(Carrier);
	for_each(ShipList->begin(), ShipList->end(), [this](Ship* s) { fill_board_auto(*s); });
}