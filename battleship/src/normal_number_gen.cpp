#include "include/normal_number_gen.h"

namespace battleship
{
	normal_number_gen::normal_number_gen(double mi, double sigma) : distribution(mi, sigma) {}

	double normal_number_gen::operator()() { return distribution(rand_engine); }
}