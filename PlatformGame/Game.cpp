#include "stdafx.h"
#include "Game.h"

Game* Game::sInstance = nullptr;

Game::Game()
{
	InitWindow();
	InitStates();
	mRunning = true;
}
Game::~Game()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	IMG_Quit();
	SDL_Quit();

	while (!this > mStates.empty())
	{
		delete this->mStates.top();
		this->mStates.pop();
	}
}



Game* Game::getInstance()
{
	return sInstance = (sInstance != nullptr) ? sInstance : new Game();
}

SDL_Renderer* Game::getRenderer()
{
	return this->mRenderer;
}

void Game::InitWindow()
{
	//Create SDL Window
	assert(SDL_Init(SDL_INIT_VIDEO) == 0 && SDL_GetError());
	SDL_WindowFlags w_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	this->mWindow = SDL_CreateWindow("Mage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 600, w_flags);
	assert(this->mWindow != nullptr && SDL_GetError());

	//Create Renderer context
	SDL_RendererFlags r_flags = (SDL_RendererFlags)(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	mRenderer = SDL_CreateRenderer(this->mWindow, -1, r_flags);
	assert(mRenderer != nullptr && SDL_GetError());


	Camera::getInstance()->SetTarger(new Point(100,100));

	Camera::getInstance()->SetSceneLimit(900, 600);
}

void Game::InitStates()
{
	this->mStates.push(new GameState(this->mWindow));
}

void Game::Update()
{
	UpdateEventSDL();
	this->time.Update();

	if (!this->mStates.empty())
	{
		this->mStates.top()->Update(time.getTick());
		if (this->mStates.top()->getExit())
		{
			this->mStates.top()->ExitEvent();
			delete this->mStates.top();
			this->mStates.pop();
		}
	}
	else
	{
		this->EndApplication();
		this->mRunning = false;
	}

	Inputs::getInstance()->Listen();

}

void Game::Render()
{
	//Draw with rgba color 
	SDL_SetRenderDrawColor(this->mRenderer, 0, 0, 250, 0);
	// Xóa mục tiêu hiển thị hiện tại bằng màu vẽ.
	SDL_RenderClear(this->mRenderer);

	if (!this->mStates.empty())
	{
		this->mStates.top()->Render(this->mRenderer);
	}

	//Cập nhật màn hình với bất kỳ kết xuất nào được thực hiện kể từ lần gọi trước.
	SDL_RenderPresent(this->mRenderer);
}

void Game::UpdateEventSDL()
{

	while (SDL_PollEvent(&mEvent))//Trả về 1 nếu có sự kiện đang chờ xử lý hoặc 0 nếu không có sự kiện nào khả dụng. https://wiki.libsdl.org/SDL_PollEvent
	{
		switch (this->mEvent.type)
		{
		case SDL_QUIT:
			this->mRunning = false;
			
		}
	}
}

void Game::Run()
{
	while (mRunning)
	{
		Render();
		Update();
		
	}

}
void Game::Quit()
{
	mRunning = false;
}
void Game::EndApplication()
{
	std::cout << "\nEnding Application...";
}


void Game::setRunning(bool running)
{
	mRunning = running;
}

bool Game::isRunning()
{
	return this->mRunning;
}
