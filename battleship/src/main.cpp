#include <iostream>
#include "include/game.h"
#include "include/exception.h"
// https://en.wikipedia.org/wiki/Battleship_(game)
// in this game battleship cannot touch
// game throws errors when a bug occured
// todo: sdl/opengl convertion, make debug fixes

int main(void)
{
	try
	{
		battleship::game* GG = new battleship::game();
		GG->create_players();
		GG->play();
		delete GG;
	}
	catch (game_exceptions::exception& E)
	{
		std::cerr << E << std::endl;
	}
	return 0;
}