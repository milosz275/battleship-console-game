#include "include/base_player.h"
// coordinates are switched due to vector of vectors characteristics
// todo: rotate m_board

namespace battleship
{
	base_player::base_player(std::string n) : m_board(NULL), m_player_name(n), m_combo(true), m_kills(0), m_ship_list(NULL) { create_board(); }

	base_player::~base_player() { delete m_board, m_ship_list; }

	void base_player::create_board(void)
	{
		if (m_board == NULL)
			m_board = new std::vector<std::vector<square>>(m_board_size, std::vector<square>(m_board_size));
		else
			throw game_exceptions::exception("Attempted to overwrite the m_board");
	};

	void base_player::print_board(std::ostream& os) // todo: iomanip
	{
		if (m_board == NULL)
			throw game_exceptions::exception("m_board is empty");
		os << "\t ";
		for (char c = 'A'; c < 'A' + m_board_size; ++c)
			os << c << "  ";
		for_each(m_board->begin(), m_board->end(), [&os, j = 0](std::vector<square>& v) mutable
			{
				os << std::endl << ++j << " \t|";
				copy(v.begin(), v.end(), std::ostream_iterator<square>(os, " |"));
			});
		os << std::endl;
	}

	void base_player::print_board_discreetly(std::ostream& os) // todo: iomanip
	{
		if (m_board == NULL)
			throw game_exceptions::exception("m_board is empty");
		os << "\t ";
		for (char c = 'A'; c < 'A' + m_board_size; ++c)
			os << c << "  ";
		for_each(m_board->begin(), m_board->end(), [&os, j = 0](std::vector<square>& v) mutable
			{
				os << std::endl << ++j << "\t|";
				for_each(v.begin(), v.end(), [&os](square& s)
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

	int base_player::get_kills(void) { return m_kills; }

	void base_player::set_combo(void) { m_combo = true; }

	const base_player& base_player::operator++() { m_kills++; return *this; }

	std::vector<std::vector<square>>* base_player::get_board(void) { return m_board; }

	std::string base_player::get_name(void) { return m_player_name; }

	base_player* base_player::set_next_player(base_player* next_player) { return m_next_player = next_player; }

	base_player* base_player::get_next_player(void) { return m_next_player; }

	void base_player::print_ship(std::ostream& os)
	{
		if (m_ship_list == NULL)
			throw game_exceptions::exception("ship list is empty");
		copy(m_ship_list->begin(), m_ship_list->end(), std::ostream_iterator<ship*>(os << "m_ship_list" << std::endl << " |", " |"));
		os << std::endl;
	}

	void base_player::hit_ship(ship* s)
	{
		all_of(m_ship_list->begin(), m_ship_list->end(), [&s](ship* c)
			{
				if (c == s)
				{
					(*c).operator++();
					return false;
				}
				return true;
			});
	}

	bool base_player::check_neighbourhood(int x, int y, int length, bool horizontally)
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
		for_each(m_board->begin() + y_start, m_board->begin() + y_end + 1, [&x_start, &x_end, &occupied](std::vector<square>& v) { for_each(v.begin() + x_start, v.begin() + x_end + 1, [&occupied](square& sq) { if (sq.check_if_contains_ship()) occupied = true; }); });

		return occupied;
	}

	void base_player::insert_boat(ship& s, int x, int y, bool horizontally)
	{
		if (horizontally)
			for_each(m_board->begin() + y, m_board->begin() + y + 1, [&x, &s, &y](std::vector<square>& v) { for_each(v.begin() + x, v.begin() + x + s.get_size(), [&s](square& sq) { sq.set_ship(s); }); });
		else
			std::for_each(m_board->begin() + y, m_board->begin() + y + s.get_size(), [&x, &s](std::vector<square>& v) { v[x].set_ship(s); });
	}

	void base_player::fill_board_auto(ship& s)
	{
		bool occupied = true;
		int x = -1;
		int y = -1;
		bool horizontal;
		int size = s.get_size();
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
			assert(x >= 0 && x < 10 && y >= 0 && y < 10);
			occupied = check_neighbourhood(x, y, s.get_size(), horizontal);
		}
		insert_boat(s, x, y, horizontal);
	}

	void base_player::create_boats_populate_auto(void)
	{
		m_ship_list = new std::list<ship*>;
		ship* Destroyer = new ship(2, "Destroyer"), * Submarine = new ship(3, "Submarine"), * Cruiser = new ship(3, "Cruiser"), * Battleship = new ship(4, "Battleship"), * Carrier = new ship(5, "Carrier");
		m_ship_list->push_back(Destroyer);
		m_ship_list->push_back(Submarine);
		m_ship_list->push_back(Cruiser);
		m_ship_list->push_back(Battleship);
		m_ship_list->push_back(Carrier);
		for_each(m_ship_list->begin(), m_ship_list->end(), [this](ship* s) { fill_board_auto(*s); });
	}

	void base_player::add_ship_to_opponent(base_player& opponent)
	{
		assert(opponent.m_opponent_ship_list == NULL);
		assert(m_ship_list != NULL);

		opponent.m_opponent_ship_list = new std::list<ship*>;

		for_each(m_ship_list->begin(), m_ship_list->end(), [&opponent](ship* s) { opponent.m_opponent_ship_list->push_back(new ship(s->get_size(), s->get_name())); });
	}
}