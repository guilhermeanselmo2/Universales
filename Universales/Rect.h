#ifndef RectH
#define RectH

#include "Point.h"

class Rect {

private:
	

public:
	Rect();
	Rect(float x, float y, float w, float h);
	void SetRect(float x, float y, float w, float h);
	void SetPosition(float x, float y);
	bool IsInside(float new_x, float new_y);
	float GetXrect() const;
	float GetYrect() const;
	float GetWrect() const;
	float GetHrect() const;
	Rect SumPoint(Point p1, Rect r1);
	Point CenterRect(Rect r1) const;
	float DisCenterRect(Rect r1, Rect r2);

	float x, y, w, h;
};

#endif
