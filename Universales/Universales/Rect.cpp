#include "Rect.h"

Rect::Rect() {
	x = 0;
	y = 0;
	h = 0;
	w = 0;
}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

float Rect::GetXrect() const {
	return x;
}
float Rect::GetYrect() const {
	return y;
}
float Rect::GetHrect() const {
	return h;
}
float Rect::GetWrect() const {
	return w;
}
void Rect::SetRect(float x, float y, float w, float h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

bool Rect::IsInside(float xi, float yi) {
	if ((x<xi) && (xi<(x + w)) && (yi>y) && (yi<(y + h)))
		return true;
	return false;
}

Rect Rect::SumPoint(Point p1, Rect r1){
	Rect result;
	result.x = r1.x + p1.GetXpoint();
	result.y = r1.y + p1.GetYpoint();
	return result;
}

Point Rect::CenterRect(Rect r1) const {
	Point result;
	float px, py;
	px = ((r1.w / 2) + r1.x);
	py = ((r1.h / 2) + r1.y);
	result.SetPoint(px, py);
	return result;
}

float Rect::DisCenterRect(Rect r1, Rect r2) {
	Point p1, p2;
	float result;
	p1 = CenterRect(r1);
	p2 = CenterRect(r2);
	result = p1.DisPoints(p1, p2);
	return result;
}

void Rect::SetPosition(float new_x, float new_y){
	x = new_x;
	y = new_y;
}