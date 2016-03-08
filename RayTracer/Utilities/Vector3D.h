#pragma once
#include "Matrix.h"

class Normal;
class Point3D;

class Vector3D {
public:
	double x, y, z;

	// Constructors
	Vector3D();
	Vector3D(const double c);
	Vector3D(const double x, const double y, const double z);
	Vector3D(const Vector3D &point);
	Vector3D(const Normal& n);						
	Vector3D(const Point3D& p);
	~Vector3D(void);

	// Operators
	Vector3D& operator= (const Vector3D& rhs);
	Vector3D& operator= (const Normal& rhs);
	Vector3D& operator= (const Point3D& rhs);
	Vector3D operator- (void) const;
	Vector3D operator* (const double a) const;
	Vector3D operator/ (const double a) const;
	Vector3D operator+ (const Vector3D& v) const;
	Vector3D& operator+= (const Vector3D& v);
	Vector3D operator- (const Vector3D& v) const;
	double operator* (const Vector3D& b) const;
	Vector3D operator^ (const Vector3D& v) const;

	// Functions
	double length(void);
	double len_squared(void);
	void  normalize(void);
	Vector3D& hat(void);
};
// Inlined member functions
inline double Vector3D::len_squared(void) {
	return (x * x + y * y + z * z);
}

// Inlined member operators
inline Vector3D Vector3D::operator- (void) const {
	return (Vector3D(-x, -y, -z));
}

inline Vector3D Vector3D::operator* (const double a) const {
	return (Vector3D(x * a, y * a, z * a));
}

inline Vector3D Vector3D::operator/ (const double a) const {
	return (Vector3D(x / a, y / a, z / a));
}

inline Vector3D Vector3D::operator+ (const Vector3D& v) const {
	return (Vector3D(x + v.x, y + v.y, z + v.z));
}

inline Vector3D Vector3D::operator- (const Vector3D& v) const {
	return (Vector3D(x - v.x, y - v.y, z - v.z));
}

inline double Vector3D::operator* (const Vector3D& v) const {
	return (x * v.x + y * v.y + z * v.z);
}

inline Vector3D Vector3D::operator^ (const Vector3D& v) const {
	return (Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x));
}

inline Vector3D& Vector3D::operator+= (const Vector3D& v) {
	x += v.x; y += v.y; z += v.z;
	return (*this);
}

inline Vector3D operator* (const double a, const Vector3D& v) {
	return (Vector3D(a * v.x, a * v.y, a * v.z));
}

// Outside operators 
Vector3D operator* (const Matrix& mat, const Vector3D& v);
Vector3D operator* (const double a, const Vector3D& v);