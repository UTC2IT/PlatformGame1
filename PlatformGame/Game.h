#ifndef GAME_H
#define	GAME_H


#include "GameState.h"


#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600

class Game
{
private:
	static Game* sInstance;

	SDL_Window* mWindow{};
	SDL_Renderer* mRenderer{};
	SDL_Event mEvent;

	Time time;

	std::stack<State*> mStates;

	float currtime;
	bool mRunning;

	void InitWindow();
	void InitStates();
public:
	Game();
	~Game();
	//setter and getter
	static Game* getInstance();
	SDL_Renderer* getRenderer();


	//Update
	void Update();
	void UpdateEventSDL();

	//Render
	void Render();
	
	//Run
	void Run();
	

	//Quit
	void Quit();
	void EndApplication();
	void setRunning(bool running);
	bool isRunning();
	

};

#endif // !