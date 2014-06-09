#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "Point.h"
#include <memory>

class Comparator
{
public:
    bool operator()(const Point& lhs, const Point& rhs);


};

#endif // COMPARATOR_H
