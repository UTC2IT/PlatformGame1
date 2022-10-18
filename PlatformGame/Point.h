#ifndef POINT_H
#define POINT_H

class Point
{
private:
	float X, Y;
public:
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	Point(float X = 0, float Y = 0);
	Point operator + (const Point& p2) const;
	// cộng các biến thành viên ttrong hàm được gọi với tham số truyền vào
	friend Point operator += (Point& p1, const Point& p2);
	Point operator -(Point const& p2) const;
	friend Point operator -= (Point& p1, const Point& p2);
	Point operator* (const float scaler) const;
};
#endif