#include "stdafx.h"
#include "State.h"

State::State()
{
}

State::State(SDL_Window* window)
{
	this->mExit = false;
	this->mWindow = window;
}

State::~State()
{

}

const bool& State::getExit() const
{
	return this->mExit;
}

void State::ExitEvent()
{
	std::cout << "Ending States....";
}

void State::Update(const float& dt)
{
	
}

void State::Render(SDL_Renderer* renderer)
{

}


void State::CheckForExit()
{
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		this->mExit = true;
	}
}
