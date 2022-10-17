#include "stdafx.h"
#include "Vector2D.h"

Vector2D::Vector2D(float x, float y) : X(x),Y(y)
{
}

float Vector2D::getX()
{
    return X;
}

float Vector2D::getY()
{
    return Y;
}

void Vector2D::setX(float x)
{
    X = x;
}

void Vector2D::setY(float y)
{
    Y = y;
}

Vector2D Vector2D::operator+(const Vector2D& v2) const
{
    return Vector2D(this->X + v2.X, this->Y + v2.Y);
}

Vector2D Vector2D::operator-(const Vector2D& v2) const
{
    return Vector2D(this->X - v2.X, this->Y - v2.Y);
}

Vector2D Vector2D::operator*(const float& T) const
{
    return Vector2D(this->X * T, this->Y * T);
}

Vector2D Vector2D::operator*(const Vector2D& v2) const
{
    return Vector2D(this->X * v2.X, this->Y * v2.Y);
}

Vector2D Vector2D::operator/(const float& T) const
{
    return Vector2D(this->X / T, this->Y / T);
}

Vector2D Vector2D::operator/(const Vector2D& v2) const
{
    return Vector2D(this->X / v2.X, this->Y / v2.Y);
}

Vector2D Vector2D::operator+=(const Vector2D& v2)
{
    this->X += v2.X; this->Y += v2.Y; return *this;
}

Vector2D Vector2D::operator-=(const Vector2D& v2)
{
    this->X -= v2.X; this->Y -= v2.Y; return *this;
}

Vector2D Vector2D::operator*=(const Vector2D& v2)
{
    this->X *= v2.X; this->Y *= v2.Y; return *this;
}

Vector2D Vector2D::operator/=(const Vector2D& v2)
{
    this->X /= v2.X; this->Y /= v2.Y; return *this;
}

void Vector2D::swap(Vector2D& v1, Vector2D& v2)
{
    Vector2D tmp;
    tmp = v1;
    v1 = v2;
    v2 = tmp;
}



