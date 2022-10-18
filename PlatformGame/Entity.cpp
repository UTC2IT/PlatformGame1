#include "stdafx.h"
#include "Entity.h"


Properties::Properties(std::string textureID, float x, float y, int width, int height, int index, SDL_RendererFlip flip) : X(x), Y(y), Flip(flip),
Width(width), Height(height),
TextureID(textureID)
{

}


Entity::Entity()
{

}

Entity::~Entity()
{

}
Entity::Entity(Properties* props) : mTransform(new Transform(props->X, props->Y)),
mTextureID(props->TextureID), mWidth(props->Width), mHeight(props->Height),
mFlip(props->Flip)
{
	float px = props->X + static_cast<float>(props->Width / 2);
	float py = props->Y + static_cast<float>(props->Height / 2);
	mOrigin = new Point(px, py);
}
