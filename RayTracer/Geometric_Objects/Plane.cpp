#include "Plane.h"
#include <math.h>
#include "../Utilities/ShadeRec.h"
#include "../Utilities/Ray.h"
#include <iostream>

const double Plane::kEpsilon = 0.001;

// Constructors
Plane::Plane(void)
	: GeometricObject(),
	a(0.0),
	dim(0),
	n(0, 1, 0)
{}

Plane::Plane(const Point3D& point, const Normal& normal)
	: GeometricObject(),
	a(point),
	dim(0),
	n(normal)
{
	n.normalize();
}

Plane::Plane(const Point3D& point, const Point3D& dim, const Normal& normal)
	: GeometricObject(),
	a(point),
	dim(dim),
	n(normal)
{
	n.normalize();
}

Plane::Plane(const Plane& plane)
	: GeometricObject(plane),
	a(plane.a),
	dim(plane.dim),
	n(plane.n)
{}

Plane::~Plane(void) {}

// Operators
Plane& Plane::operator= (const Plane& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	a = rhs.a;
	dim = rhs.dim;
	n = rhs.n;

	return (*this);
}

// Operations
Plane* Plane::clone(void) const {
	return (new Plane(*this));
}

bool Plane::hit(const Ray &ray, double &tmin, ShadeRec &sr) const {

	double t = (a - ray.o) * n / (ray.d *n) ;

	if (t > kEpsilon) {
		tmin = t;
		sr.normal = n;
		sr.local_hit_point = ray.o + t * ray.d;
		if (dim.x == 0 && dim.y == 0 && dim.z == 0) {
			return true;
		}
		else if (abs(sr.local_hit_point.x - a.x) > dim.x &&
			abs(sr.local_hit_point.y - a.y) > dim.y) {
			return true;
		}
	}
	else {
		return false;
	}
}

bool Plane::shadow_hit(const Ray &ray, double &tmin) const {
	float t = (a - ray.o) * n / (ray.d * n);

	if (t > kEpsilon) {
		tmin = t;
		return true;
	}
	return false;
}