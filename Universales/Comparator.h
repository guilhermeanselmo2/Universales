#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "Point.h"
#include <memory>
#include <iostream>

using namespace std;

class Comparator
{
public:
    bool operator()(const Point& lhs, const Point& rhs);


};

#endif // COMPARATOR_H
