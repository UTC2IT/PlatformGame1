#ifndef ENTITY_H
#define ENTITY_H

#include "stdafx.h"
#include "Time.h"
#include "Camera.h"

class Entity
{
private:

protected:

	SDL_FRect mPlayer;
	float mMovementSpeed;


public:
	Entity();
	virtual ~Entity();

	void move(const float& dt, const float& x, const float& y);

	virtual void Update(const float& dt);
	virtual void Render(SDL_Renderer* renderer);

};

#endif // !ENTITY_H
