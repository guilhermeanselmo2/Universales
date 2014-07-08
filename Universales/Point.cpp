#include "Point.h"
#include <SDL_stdinc.h>
Point::Point() {}

Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}

void Point::SetPoint(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Point::GetXpoint() const {
	return x;
}
void Point::SetXpoint(float x) {
	this->x = x;
}
void  Point::SetYpoint(float y) {
	this->y = y;
}
float Point::GetYpoint() const {
	return y;
}

float Point::DisPoints(Point p1, Point p2) {
	float result;
	result = sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
	return result;
}

float Point::DisPoints(float x, float y, Point p1) {
	float result;
	result = sqrt((p1.x - x)*(p1.x - x) + (p1.y - y)*(p1.y - y));
	return result;
}

Point Point::SumPoints(Point p1, Point p2) {
	Point result;
	result.x = p1.x + p2.x;
	result.y = p1.y + p2.y;
	return result;
}
Point Point::SubPoints(Point p1, Point p2) {
	Point result;
	result.x = p1.x - p2.x;
	result.y = p1.y - p2.y;
	return result;
}
float Point::Inclinacao(Point p1, Point p2){
	float result;
	if (p1.y > p2.y) {
		if (p1.x > p2.x) {
			result = (p2.y - p1.y) / (p2.x - p1.x);
			result = atan(result);
		}
		if (p1.x < p2.x) {
			result = (p1.x - p2.x) / (p1.y - p2.y);
			result = atan(result*-1) + (M_PI / 2);
		}
	}
	if (p1.y < p2.y){
		if (p1.x > p2.x) {
			result = (p2.y - p1.y) / (p2.x - p1.x);
			result = atan(result);
		}
		if (p1.x < p2.x){
			result = (p1.x - p2.x) / (p1.y - p2.y);
			result = atan(result*-1) - (M_PI / 2);
		}
	}
	return result;
}

float Point::Inclinacao(float x,float y, Point p1){
	float result;
	if (y >= p1.y) {
		if (x >= p1.x) {
			result = (p1.y - y) / (p1.x - x);
			result = atan(result);
		}
		if (x < p1.x) {
			result = (x - p1.x) / (y - p1.y);
			result = atan(result*-1) + (M_PI / 2);
		}
	}
	if (y < p1.y){
		if (x >= p1.x) {
			result = (p1.y - y) / (p1.x - x);
			result = atan(result);
		}
		if (x < p1.x){
			result = (x - p1.x) / (y - p1.y);
			result = atan(result*-1) - (M_PI / 2);
		}
	}
	return result;
}


 Point Point::operator+(const Point& rhs) const {
    return Point(x + rhs.x, y + rhs.y);
}

Point Point::operator-(const Point& rhs) const {
    return Point(x - rhs.x, y - rhs.y);
}

Point Point::operator*(const float rhs) const {
    return Point(x * rhs, y * rhs);
}

float Point::GetDistance(Point p){
    int px, py;
    px = p.x;
    py = p.y;
    return sqrt(pow(px-x,2) + pow(py-y,2));
}

float Point::GetDistance(float px, float py){
    return sqrt(pow(px-x,2) + pow(py-y,2));
}