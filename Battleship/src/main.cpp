#include <iostream>
#include "Game.h"
#include "Exception.h"
// https://en.wikipedia.org/wiki/Battleship_(game)
// in this game battleship cannot touch
// game throws errors when a bug occured
// todo: sdl/opengl convertion

int main(int argc, char* argv[])
{
	try
	{
		Battleship::Game* GG = new Battleship::Game();
		GG->play();
		delete GG;
	}
	catch (Exception& E)
	{
		std::cout << E << std::endl;
	}
	return 0;
}