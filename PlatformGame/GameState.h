#ifndef GAMESTATE_H
#define GAMESTATE_H


#include "State.h"

class GameState :
    public State
{
private:
    Entity mPlayer;

public:
    GameState();
    GameState(SDL_Window* window);
    virtual ~GameState();


    virtual void UpdateInput(const float& dt);
    virtual void Update(const float& dt);
    virtual void Render(SDL_Renderer* renderer);
   

};

#endif 