#include "CostComparator.h"


bool CostComparator::operator()(const Point& lhs, const Point& rhs) {
	if (lhs.z > rhs.z){
		return true;
	}
	else{
		return false;
	}
}
