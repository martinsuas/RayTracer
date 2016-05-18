/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include <math.h>
#include "Normal.h"

// Constructors 
Normal::Normal(void) : x(0.0), y(0.0), z(0.0) {}
Normal::Normal(double c) : x(c), y(c), z(c) {}
Normal::Normal(double x, double y, double z) : x(x), y(y), z(z) {}
Normal::Normal(const Normal &n) : x(n.x), y(n.y), z(n.z) {}
Normal::Normal(const Vector3D& v) : x(v.x), y(v.y), z(v.z) {}
Normal::~Normal(void) {}

// Operators
Normal& Normal::operator= (const Normal& rhs) {
	if (this == &rhs)
		return (*this);
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}

Normal& Normal::operator= (const Vector3D& rhs) {
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}

Normal& Normal::operator= (const Point3D& rhs) {
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}

// Operations
void Normal::normalize(void) {
	double length = sqrt(x * x + y * y + z * z);
	x /= length; y /= length; z /= length;
}

// Out of class functions
/*
A normal is transformed by multiplying it on the left by the transpose of the upper left 3 x 3
partition of the inverse transformation matrix
Credit - book
*/
Normal operator* (const Matrix& mat, const Normal& n) {
	return (Normal(mat.m[0][0] * n.x + mat.m[1][0] * n.y + mat.m[2][0] * n.z,
		mat.m[0][1] * n.x + mat.m[1][1] * n.y + mat.m[2][1] * n.z,
		mat.m[0][2] * n.x + mat.m[1][2] * n.y + mat.m[2][2] * n.z));
}

