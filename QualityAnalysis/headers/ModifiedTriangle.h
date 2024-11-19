#pragma once

#include "Triangle.h"

class ModifiedTriangle : public Geometry::Triangle
{
    double color[3] = {0, 1, 0};
public:
    ModifiedTriangle();
    ~ModifiedTriangle();
    ModifiedTriangle(Geometry::Point& normal, Geometry::Point& p1, Geometry::Point& p2, Geometry::Point& p3);
    ModifiedTriangle(const Geometry::Point& normal, const Geometry::Point& p1, const Geometry::Point& p2, const Geometry::Point& p3, const double color[3]);
};
