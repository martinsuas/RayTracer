/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include "Ray.h"
// Constructors
Ray::Ray (void) : o(0.0), d(0.0, 0.0, 1.0) {}
Ray::Ray(const Point3D& origin, const Vector3D &dir) 
	: o(origin), d(dir) {}
Ray::Ray(const Ray &ray) : o(ray.o), d(ray.d) {}
Ray::~Ray(void) {}

// Operators
Ray& Ray::operator= (const Ray &rhs) {

	if (this == &rhs)
		return (*this);

	o = rhs.o;
	d = rhs.d;

	return (*this);
}
