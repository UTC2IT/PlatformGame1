#include "stdafx.h"
#include "Transform.h"

Transform::Transform(float x, float y) : X(x), Y(y)
{
}

float Transform::getX()
{
	return X;
}

float Transform::getY()
{
	return Y;
}

void Transform::setX(float x)
{
	X = x;
}

void Transform::setY(float y)
{
	Y = y;
}

void Transform::translatex(float x)
{
	this->X += x;
}

void Transform::translatey(float y)
{
	this->Y += y;
}

void Transform::translate(Vector2D v)
{
	this->X += v.getX();
	this->Y += v.getY();
}
