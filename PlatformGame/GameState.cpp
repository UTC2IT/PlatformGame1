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
	
	
}

void GameState::Update(const float& dt)
{
	this->UpdateInput(dt);



	Camera::getInstance()->Update(dt);
}

void GameState::Render(SDL_Renderer* renderer)
{
	
}
