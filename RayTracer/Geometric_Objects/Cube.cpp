#include "Cube.h"
#include <math.h>

const double Cube::kEpsilon = 0.001;

// Constructors
Cube::Cube(void) : GeometricObject(), center(0.0), dim(1.0) {}

Cube::Cube(Point3D c, Point3D d) : GeometricObject(), center(c), dim(d) {}

Cube* Cube::clone(void) const {
	return (new Cube(*this));
}

Cube::Cube(const Cube& cub)
	: GeometricObject(cub), center(cub.center), dim(cub.dim) {}

Cube::~Cube(void) {}

// Operators
Cube& Cube::operator= (const Cube& cub)
{
	if (this == &cub)
		return (*this);
	GeometricObject::operator= (cub);
	center = cub.center;
	dim = cub.dim;
	return (*this);
}

// Operations
bool Cube::hit(const Ray &ray, double &tmin, ShadeRec &sr) const {
	double		t;
	Vector3D	temp = ray.o - center;
	double		a = ray.d * ray.d;
	double		b = 2.0 * temp * ray.d;
	double		c = temp * temp;// -radius * radius;
	double		discr = b * b - 4.0 * a * c;

	if (discr < 0.0)
		return false;
	else {
		double e = sqrt(discr);
		double denom = 2.0 * a;
		t = (-b - e) / denom;

		if (t > kEpsilon) {
			tmin = t;
			sr.normal = (temp + t * ray.d);// / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return true;
		}

		t = (-b + e) / denom;

		if (t > kEpsilon) {
			tmin = t;
			sr.normal = (temp + t * ray.d);// / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return true;
		}
	}
	return false;
}

bool Cube::shadow_hit(const Ray &ray, double &tmin) const {
	return false;
}