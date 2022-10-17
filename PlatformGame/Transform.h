#include "Vector2D.h"
#ifndef TRANSFORM_H
#define TRANSFORM_H
class Transform
{
private:
	float X, Y;
public:
	Transform(float x = 0, float y = 0);
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	
	void translatex(float x);
	void translatey(float y);
	void translate(Vector2D v);
};
#endif

