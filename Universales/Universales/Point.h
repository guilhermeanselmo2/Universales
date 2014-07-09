#ifndef PointH
#define PointH

#include <math.h>

class Point {

private:
	

public:
	Point();
	Point(float x, float y, float z = 0);
	void SetPoint(float x, float y, float z = 0);
	Point operator+(const Point& rhs) const;
	Point operator-(const Point& rhs) const;
	Point operator*(const float rhs) const;
	float GetXpoint() const;
	float GetYpoint() const;
	void SetXpoint(float x);
	void SetYpoint(float y);
	float DisPoints(Point p1, Point p2);
	float DisPoints(float x, float y, Point p1);
	float GetDistance(Point p);
    float GetDistance(float px, float py);
	Point SubPoints(Point p1, Point p2);
	Point SumPoints(Point p1, Point p2);
	float Inclinacao(Point p1, Point p2);
	float Inclinacao(float x, float y, Point p2);

	float x, y, z;
};

#endif