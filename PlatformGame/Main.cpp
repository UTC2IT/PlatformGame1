#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
int main(int argc, char** argv)
{
	Game game;
	while (game.isRunning())
	{
		game.Quit();
	}
	return 0;
}