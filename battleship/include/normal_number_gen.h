#ifndef NORMAL_NUMBER_GEN_H
#define NORMAL_NUMBER_GEN_H

#include <random>

namespace battleship
{
	class normal_number_gen
	{
		// 
		static std::default_random_engine rand_engine;
		// 
		std::normal_distribution<double> distribution;
	public:
		normal_number_gen(double mi = 0, double sigma = 1);
		double operator()();
	};
	std::default_random_engine normal_number_gen::rand_engine;
}

#endif // !NORMAL_NUMBER_GEN_H
