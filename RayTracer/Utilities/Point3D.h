/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "Matrix.h"
#include "Vector3D.h"

class Point3D {
public:
	double x, y, z;
	// Constructors
	Point3D();
	Point3D(const double c);
	Point3D(const double x, const double y, const double z);
	Point3D(const Point3D &point);
	~Point3D(void);

	// Operators
	Point3D& operator= (const Point3D& p);
	Point3D operator- (void) const;
	Vector3D operator- (const Point3D& p) const;
	Point3D operator+ (const Vector3D& v) const;
	Point3D operator- (const Vector3D& v) const;
	Point3D operator* (const double a) const;

	// Operations
	double d_squared(const Point3D& p) const;

	double distance(const Point3D& p) const;
};
// Inline member functions
inline Point3D Point3D::operator- (void) const {
	return (Point3D(-x, -y, -z));
}

inline Vector3D Point3D::operator- (const Point3D& p) const {
	return (Vector3D(x - p.x, y - p.y, z - p.z));
}

inline Point3D Point3D::operator+ (const Vector3D& v) const {
	return (Point3D(x + v.x, y + v.y, z + v.z));
}

inline Point3D Point3D::operator- (const Vector3D& v) const {
	return (Point3D(x - v.x, y - v.y, z - v.z));
}


inline Point3D Point3D::operator* (const double a) const {
	return (Point3D(x * a, y * a, z * a));
}

inline double Point3D::d_squared(const Point3D& p) const {
	return ((x - p.x) * (x - p.x)
		+ (y - p.y) * (y - p.y)
		+ (z - p.z) * (z - p.z));
}

// Inlined non-member function
Point3D operator* (double a, const Point3D& p);

inline Point3D operator* (double a, const Point3D& p) {
	return (Point3D(a * p.x, a * p.y, a * p.z));
}

// Non-inlined non-member function
Point3D operator* (const Matrix& mat, const Point3D& p);
