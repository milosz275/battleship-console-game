#include "include/Ship.h"

int Ship::getSize(void) { return size; }

int Ship::getHits(void) { return hits; }

const Ship* Ship::operator++() { hits++; return this; }

std::string Ship::getName(void) { return name; }

Ship::Ship(int s, std::string n) : size(s), name(n), hits(0) {};

bool Ship::operator==(const Ship* s) { return name == s->name; }	
	
std::ostream& operator<<(std::ostream& os, const Ship* S) { return os << "ship name: " << S->name << "\t size: " << S->size << "\t hits: " << S->hits << std::endl; }