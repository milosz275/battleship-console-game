#include <iostream>
#include "include/Game.h"
#include "include/Exception.h"
// https://en.wikipedia.org/wiki/Battleship_(game)
// in this game battleship cannot touch
// game throws errors when a bug occured
// todo: sdl/opengl convertion, make debug fixes

int main(int argc, char* argv[])
{
	try
	{
		battleship::game* GG = new battleship::game();
		GG->play();
		delete GG;
	}
	catch (game_exceptions::exception& E)
	{
		std::cerr << E << std::endl;
	}
	return 0;
}