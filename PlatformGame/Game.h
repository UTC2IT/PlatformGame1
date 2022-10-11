#pragma once
#include "stdafx.h"

class Game
{
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mRunning;
	
public:
	Game();
	~Game();
	void Update();
	void Render();
	void UpdateEventSDL();
	void Run();
	void Quit();
	bool isRunning() { return mRunning; }

};

