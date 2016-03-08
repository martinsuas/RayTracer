#include "Point2D.h"
// Constructors 
Point2D::Point2D() :
	x(0.0), y(0.0)
{}
Point2D::Point2D(const float a) :
	x(a), y(x)
{}
Point2D::Point2D(const float _x, const float _y) :
	x(_x), y(_y)
{}
Point2D::Point2D(const Point2D &o) :
	x(o.x), y(o.y)
{}
Point2D::~Point2D() {}

// Operator
Point2D& Point2D::operator=(const Point2D &o) {
	if (this == &o)
		return *this;
	x = o.x;
	y = o.y;
	return *this;
}