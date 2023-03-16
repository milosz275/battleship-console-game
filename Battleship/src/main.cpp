#include <iostream>
#include "Game.h"
#include "Exception.h"
// https://en.wikipedia.org/wiki/Battleship_(game)
// in this game battleship cannot touch
// game throws errors when a bug occured

int main(int argc, char* argv[])
{
	try
	{
		Battleship::Game GG;
		GG.play();
	}
	catch (Exception& e)
	{
		std::cout << e;
	}

	return 0;
}