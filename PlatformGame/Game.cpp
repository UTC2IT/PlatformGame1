#include "Game.h"


Game::Game()
{
	Update();
	mRunning = true;
}
Game::~Game()
{
	
}

void Game::Update()
{
	UpdateEventSDL();
}

void Game::Render()
{
	
}

void Game::UpdateEventSDL()
{
	assert(SDL_Init(SDL_INIT_VIDEO) == 0 && SDL_GetError());
	SDL_WindowFlags w_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	mWindow = SDL_CreateWindow("Mage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 600, w_flags);
	assert(mWindow != nullptr && SDL_GetError());

	//Create Renderer context
	SDL_RendererFlags r_flags = (SDL_RendererFlags)(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	mRenderer = SDL_CreateRenderer(mWindow, -1, r_flags);
	assert(mRenderer != nullptr && SDL_GetError());
}

void Game::Run()
{
	
}
void Game::Quit()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))//Trả về 1 nếu có sự kiện đang chờ xử lý hoặc 0 nếu không có sự kiện nào khả dụng. https://wiki.libsdl.org/SDL_PollEvent
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mRunning = false;
		}
	}
}
