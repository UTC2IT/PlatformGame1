
#include "Entity.h"

Entity::Entity()
{
	this->mPlayer = { 0.f,0.f,50.f,50.f };
	this->mMovementSpeed = 100.0f;
}

Entity::~Entity()
{

} 

void Entity::move(const float& dt, const float& x, const float& y)
{
	this->mPlayer.x += dt * x * this->mMovementSpeed;
	this->mPlayer.y += dt * y * this->mMovementSpeed;
	
}


void Entity::Update(const float& dt)
{
	
}

void Entity::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 100, 0, 0,250);
	SDL_RenderFillRectF(renderer, &this->mPlayer);
}
