#include "stdafx.h"
#include "Point.h"

float Point::getX()
{
    return X;
}

float Point::getY()
{
    return Y;
}
void Point::setX(float x)
{
    X = x;
}

void Point::setY(float y)
{
    Y = y;
}

Point::Point(float X, float Y) : X(X),Y(Y)
{
    
}

Point Point::operator+(const Point& p2) const
{
    return Point(X + p2.X, Y + p2.Y);
}

Point Point::operator-(Point const& p2) const
{
    return Point(X - p2.X, Y - p2.Y);
}

Point Point::operator*(const float scaler) const
{
    return Point(X * scaler, Y * scaler);
}

Point operator+=(Point& p1, const Point& p2)
{
    p1.X += p2.X;
    p1.Y += p2.Y;
    return p1;
}

Point operator-=(Point& p1, const Point& p2)
{
    p1.X -= p2.X;
    p1.Y -= p2.Y;
    return p1;
}
