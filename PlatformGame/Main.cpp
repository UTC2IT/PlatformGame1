#include "stdafx.h"
#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	while (game.isRunning())
	{
		game.Quit();
	}
	return 0;
}