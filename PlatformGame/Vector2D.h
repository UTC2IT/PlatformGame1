#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
private:
	friend class Collision;
	float X, Y;
public:
	Vector2D(float x = 0, float y = 0);
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);

	Vector2D operator + (const Vector2D& v2) const;
	Vector2D operator - (const Vector2D& v2) const;
	Vector2D operator * (const float& T) const;
	Vector2D operator * (const Vector2D& v2) const;
	Vector2D operator / (const float& T) const;
	Vector2D operator / (const Vector2D& v2) const;
	Vector2D operator += (const Vector2D& v2);
	Vector2D operator -= (const Vector2D& v2);
	Vector2D operator *= (const Vector2D& v2);
	Vector2D operator /= (const Vector2D& v2);

	void swap(Vector2D& v1, Vector2D& v2);

};

#endif

