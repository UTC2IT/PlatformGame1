#include "Game.h"
#include "stdafx.h"

int main(int argc, char** argv)
{
	Game game;
	while (game.isRunning())
	{
		game.Quit();
	}

	return 0;
}