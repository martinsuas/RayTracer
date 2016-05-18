/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include <math.h>
#include "Point3D.h"
// Constructors
Point3D::Point3D() : x(0.0), y(0.0), z(0.0) {}
Point3D::Point3D(double c) : x(c), y(c), z(c) {}
Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
Point3D::Point3D(const Point3D &p) : x(p.x), y(p.y), z(p.z) {}
Point3D::~Point3D(void) {}

// Operators
Point3D& Point3D::operator= (const Point3D& rhs) {
	if (this == &rhs)
		return (*this);
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}

double Point3D::distance(const Point3D& p) const {
	return (sqrt((x - p.x) * (x - p.x)
		+ (y - p.y) * (y - p.y)
		+ (z - p.z) * (z - p.z)));
}

// Non - member function
Point3D operator* (const Matrix& mat, const Point3D& p) {
	return (Point3D(mat.m[0][0] * p.x + mat.m[0][1] * p.y + mat.m[0][2] * p.z + mat.m[0][3],
		mat.m[1][0] * p.x + mat.m[1][1] * p.y + mat.m[1][2] * p.z + mat.m[1][3],
		mat.m[2][0] * p.x + mat.m[2][1] * p.y + mat.m[2][2] * p.z + mat.m[2][3]));
}