#include <iostream>
#include "Game.h"
#include "Exception.h"

int main(int argc, char* argv[])
{
	try
	{
		Battleship::Game GG;
	}
	catch (Exception& e)
	{
		std::cout << e;
	}

	return 0;
}