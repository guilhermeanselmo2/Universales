#include "Comparator.h"

bool Comparator::operator()(const Point& lhs, const Point& rhs) {
    if ((lhs.z + lhs.y> rhs.z + rhs.y)){
        return true;
    }
    else{
        if((lhs.z + lhs.y< rhs.z + rhs.y))
            return false;
        else{
            if(lhs.z < lhs.y)
                return true;
            else
                false;
        }
    }
}
