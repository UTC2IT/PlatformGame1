#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:

	Vector2D(float x = 0, float y = 0) : X(x), Y(y) {}
	inline float GetX()
	{
		return X;
	}
	inline float GetY()
	{
		return Y;
	}
	void SetX(float x)
	{
		X = x;
	}
	void SetY(float y)
	{
		Y = y;
	}

public:
	inline Vector2D  operator +  (const Vector2D& v2) const { return Vector2D(this->X + v2.X, this->Y + v2.Y); }
	inline Vector2D  operator -  (const Vector2D& v2) const { return Vector2D(this->X - v2.X, this->Y - v2.Y); }
	inline Vector2D operator  *  (const float& T) const { return Vector2D(this->X * T, this->Y * T); }
	inline Vector2D  operator *  (const Vector2D& v2) const { return Vector2D(this->X * v2.X, this->Y * v2.Y); }

	inline Vector2D operator  /  (const float& T) const { return Vector2D(this->X / T, this->Y / T); }
	inline Vector2D  operator /  (const Vector2D& v2) const { return Vector2D(this->X / v2.X, this->Y / v2.Y); }
	inline Vector2D& operator += (const Vector2D& v2) { this->X += v2.X; this->Y += v2.Y; return *this; }

	inline Vector2D& operator -= (const Vector2D& v2) { this->X -= v2.X; this->Y -= v2.Y; return *this; }

	inline Vector2D& operator *= (const Vector2D& v2) { this->X *= v2.X; this->Y *= v2.Y; return *this; }
	inline Vector2D& operator /= (const Vector2D& v2) { this->X /= v2.X; this->Y /= v2.Y; return *this; }


private:
	friend class Collision;
	friend class Warrior;
	friend class Enemy;
	float X, Y;
	//float getm_X()
	//{
	//	return m_X;
	//}

	//float getm_Y()
	//{
	//	return m_Y;
	//}

};


#endif

