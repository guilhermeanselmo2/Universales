#pragma once
#include "Point.h"
class CostComparator
{
public:
	bool operator()(const Point& lhs, const Point& rhs);
};

