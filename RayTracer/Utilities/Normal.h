/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "Matrix.h"
#include "Vector3D.h"
#include "Point3D.h"
/*
Class used to represent a normal on a surface.
*/
class Normal {
public:
	double x, y, z;
public:
	// Constructors
	Normal(void);
	Normal(double c);
	Normal(double x, double y, double z);
	Normal(const Normal &normal);
	Normal(const Vector3D& v);
	~Normal(void);

	// Operators
	Normal& operator= (const Normal& rhs);
	Normal& operator= (const Vector3D& rhs);
	Normal& operator= (const Point3D& rhs);
	Normal operator- (void) const;
	Normal operator+ (const Normal& n) const;
	Normal& operator+= (const Normal& n);
	double operator* (const Vector3D& v) const;
	Normal operator* (const double a) const;

	// Operations
	void  normalize(void);
};

// Inline member operators
inline Normal Normal::operator- (void) const {
	return (Normal(-x, -y, -z));
}

inline Normal Normal::operator+ (const Normal& n) const {
	return (Normal(x + n.x, y + n.y, z + n.z));
}

inline Normal& Normal::operator+= (const Normal& n) {
	x += n.x; y += n.y; z += n.z;
	return (*this);
}

inline double Normal::operator* (const Vector3D& v) const {
	return (x * v.x + y * v.y + z * v.z);
}

// Non-inline member operators
inline Normal Normal::operator* (const double a) const {
	return (Normal(x * a, y * a, z * a));
}

Normal operator* (const double a, const Normal& n);

inline Normal operator*(const double f, const Normal& n) {
	return (Normal(f * n.x, f * n.y, f * n.z));
}

Vector3D operator+ (const Vector3D& v, const Normal& n);

inline Vector3D operator+ (const Vector3D& v, const Normal& n) {
	return (Vector3D(v.x + n.x, v.y + n.y, v.z + n.z));
}

Vector3D operator- (const Vector3D&, const Normal& n);

inline Vector3D operator- (const Vector3D& v, const Normal& n) {
	return (Vector3D(v.x - n.x, v.y - n.y, v.z - n.z));
}

double operator* (const Vector3D& v, const Normal& n);

inline double operator* (const Vector3D& v, const Normal& n) {
	return (v.x * n.x + v.y * n.y + v.z * n.z);
}

// Out of class functions
Normal operator* (const Matrix& mat, const Normal& n);

