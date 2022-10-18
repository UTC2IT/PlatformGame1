#include "stdafx.h"
#include "Collider.h"

SDL_FRect Collider::getBox()
{
	return mBox;
}

void Collider::setBuffer(float x, float y, float w, float h)
{
	mBuffer = { x,y,w,h };
}

SDL_FRect Collider::getBuffer()
{
	return mBuffer;
}

void Collider::setBox(float x, float y, float w, float h)
{
	mBox =
	{
		x - mBuffer.x, y - mBuffer.y, w - mBuffer.w, h - mBuffer.h
	};
}

void Collider::setTileSetBox1(float x, float y, float w, float h)
{
	mTileSetBox1 = { x,y,w,h };
}

void Collider::setTileSetBox2(float x, float y, float w, float h)
{
	mTileSetBox2 = { x,y,w,h };
}

void Collider::setSkillHitBox(SDL_FRect skillhitbox)
{
	mSkillHitBox = skillhitbox;
}

SDL_FRect Collider::getSkillHitBox()
{
	return mSkillHitBox;
}

SDL_FRect Collider::getTileSetBox1()
{
	return mTileSetBox1;
}

SDL_FRect Collider::getTileSetBox2()
{
	return mTileSetBox2;
}