#ifndef ENTITY_H
#define ENTITY_H

#include "IObject.h"

struct Properties
{
public:
	Properties(std::string textureID, float x, float y, int width, int height, int index, SDL_RendererFlip flip = SDL_FLIP_NONE);
public:
	float X, Y;
	int Width, Height;
	std::string TextureID;
	SDL_RendererFlip Flip;

};

class Entity : public IObject
{
protected:
	Entity() {};

	Point* mOrigin = nullptr;
	Transform* mTransform = nullptr;
	int mWidth = 0, mHeight = 0;
	std::string mTextureID = {};
	SDL_RendererFlip mFlip = {};

public:

	Entity(Properties* props);
	Point* getOrigin() { return mOrigin; }
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;

	virtual bool CheckLastAnimation() = 0;
	virtual inline Collider* getCollider() = 0;
	virtual void setIsAttacked(bool isattacked, int damage) = 0;
	virtual void setDirectionAttacked(int derection) = 0;

};
#endif // !ENTITY_H
