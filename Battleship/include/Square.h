#ifndef SQUARE_H
#define SQUARE_H

#include "Exception.h"
#include "Ship.h"

class Square
{

	Ship* ship;

	bool isHit;
public:

	Square();

	bool check_if_contains_ship(void);

	bool check_if_hit(void);

	Ship* getShip(void);

	void setHit(void);

	void setShip(Ship& S);

	void deleteShip(void);

	friend std::ostream& operator<<(std::ostream& os, const Square& S);
};

#endif