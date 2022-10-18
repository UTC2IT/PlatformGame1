#ifndef POINT_H
#define POINT_H

class Point
{
public:
	inline float GetX()
	{
		return X;
	}
	inline float GetY()
	{
		return Y;
	}
	inline void SetX(float x)
	{
		X = x;
	}
	inline void SetY(float y)
	{
		Y = y;
	}
public:
	Point(float X = 0, float Y = 0) :X(X), Y(Y) {}

	//addition
	inline Point operator + (const Point& p2) const //cộng các biến thành viên trong hàm được gọi với tham số truyền vào
	{
		return Point(X + p2.X, Y + p2.Y);
	}
	inline friend Point operator += (Point& p1, const Point& p2) //friend dùng để nạp chồng toán tử hai ngôi 
	{
		p1.X += p2.X;
		p1.Y += p2.Y;
		return p1;
	}
	//Subtraction
	inline Point operator -(Point const& p2) const
	{
		Point(X - p2.X, Y - p2.Y);
	}
	inline friend Point operator -= (Point& p1, const Point& p2)//chỉ cần 1 biến thay đổi nên truyền tham chiếu hằng cho p2
	{
		p1.X -= p2.X;
		p1.Y -= p2.Y;
		return p1;
	}
	//Mutiplication
	inline Point operator* (const float scaler) const
	{
		return Point(X * scaler, Y * scaler);
	}

private:
	float X, Y;
};

#endif