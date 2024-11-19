#include "ModifiedTriangle.h"

ModifiedTriangle::ModifiedTriangle()
{
}

ModifiedTriangle::ModifiedTriangle(Geometry::Point& normal, Geometry::Point& p1, Geometry::Point& p2, Geometry::Point& p3) : Geometry::Triangle(normal, p1, p2, p3)
{
}

ModifiedTriangle::ModifiedTriangle(const Geometry::Point& normal, const Geometry::Point& p1, const Geometry::Point& p2, const Geometry::Point& p3, const double color[3]) : Geometry::Triangle(normal, p1, p2, p3)
{
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
}

ModifiedTriangle::~ModifiedTriangle()
{
}
