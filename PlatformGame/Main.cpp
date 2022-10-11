#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
int main(int argc, char** argv)
{
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	assert(SDL_Init(SDL_INIT_VIDEO) == 0 && SDL_GetError());
	SDL_WindowFlags w_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	m_Window = SDL_CreateWindow("Mage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 600, w_flags);
	assert(m_Window != nullptr && SDL_GetError());

	//Create Renderer context
	SDL_RendererFlags r_flags = (SDL_RendererFlags)(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_Renderer = SDL_CreateRenderer(m_Window, -1, r_flags);
	assert(m_Renderer != nullptr && SDL_GetError());

	return 0;
}