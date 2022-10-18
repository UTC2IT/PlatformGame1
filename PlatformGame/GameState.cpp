#include "stdafx.h"
#include "GameState.h"

GameState::GameState()
{
}
GameState::GameState(SDL_Window* window):
	State(window)
{

}

GameState::~GameState()
{
}

void GameState::UpdateInput(const float& dt)
{

	this->CheckForExit();	
	
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_A])
	{
		this->mPlayer.move(dt, -1.f, 0.f);
	}
	if (state[SDL_SCANCODE_D])
	{
		this->mPlayer.move(dt, 1.f, 0.f);
	}
	if (state[SDL_SCANCODE_S])
	{
		this->mPlayer.move(dt, 0.f, 1.f);
	}
	if (state[SDL_SCANCODE_W])
	{
		this->mPlayer.move(dt, 0.f, -1.f);
	}

}

void GameState::Update(const float& dt)
{
	this->UpdateInput(dt);

	this->mPlayer.Update(dt);

	Camera::getInstance()->Update(dt);
}

void GameState::Render(SDL_Renderer* renderer)
{
	this->mPlayer.Render(renderer);
}
