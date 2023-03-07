#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <string>

class Ship
{

	int size;

	int hits;

	std::string name;
public:

	int getSize(void);

	int getHits(void);

	const Ship* operator++();

	std::string getName(void);

	Ship(int s, std::string n);

	bool operator==(const Ship* s);

	friend std::ostream& operator<<(std::ostream& os, const Ship* S);
};

#endif