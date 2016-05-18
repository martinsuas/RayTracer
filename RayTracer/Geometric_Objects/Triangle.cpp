#include "../Utilities/Constants.h"
#include "Triangle.h"
#include <algorithm>
using std::min; using std::max;


Triangle::Triangle(void)
	: GeometricObject(),
	p0(0, 0, 0),
	p1(0, 0, 1),
	p2(1, 0, 0),
	normal(0, 1, 0)
{}

Triangle::Triangle(const Point3D& a, const Point3D& b, const Point3D& c)
	: GeometricObject(),
	p0(a),
	p1(b),
	p2(c)
{
	normal = (p1 - p0) ^ (p2 - p0);
	normal.normalize();
}


Triangle*
Triangle::clone(void) const {
	return (new Triangle(*this));
}

Triangle::Triangle(const Triangle& triangle)
	: GeometricObject(triangle),
	p0(triangle.p0),
	p1(triangle.p1),
	p2(triangle.p2),
	normal(triangle.normal)
{}

Triangle&
Triangle::operator= (const Triangle& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);

	p0 = rhs.p0;
	p1 = rhs.p1;
	p2 = rhs.p2;
	normal = rhs.normal;

	return (*this);
}

Triangle::~Triangle(void) {}

BBox Triangle::get_bounding_box(void) const {
	double delta = 0.00000;

	return (
		BBox(
			min(min(p0.x, p1.x), p2.x) - delta, 
			min(min(p0.y, p1.y), p2.y) - delta,
			min(min(p0.z, p1.z), p2.z) - delta,
			max(max(p0.x, p1.x), p2.x) + delta,
			max(max(p0.y, p1.y), p2.y) + delta,
			max(max(p0.z, p1.z), p2.z) + delta)
		);
}

bool
Triangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double a = p0.x - p1.x, b = p0.x - p2.x, c = ray.d.x, d = p0.x - ray.o.x;
	double e = p0.y - p1.y, f = p0.y - p2.y, g = ray.d.y, h = p0.y - ray.o.y;
	double i = p0.z - p1.z, j = p0.z - p2.z, k = ray.d.z, l = p0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double inv_denom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

	if (beta < 0.0)
		return (false);

	double r = r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;

	if (gamma < 0.0)
		return (false);

	if (beta + gamma > 1.0)
		return (false);

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

	if (t < kEpsilon)
		return (false);

	tmin = t;
	sr.normal = normal;
	sr.local_hit_point = ray.o + t * ray.d;

	return (true);
}

bool
Triangle::shadow_hit(const Ray& ray, double& tmin) const {
	double a = p0.x - p1.x, b = p0.x - p2.x, c = ray.d.x, d = p0.x - ray.o.x;
	double e = p0.y - p1.y, f = p0.y - p2.y, g = ray.d.y, h = p0.y - ray.o.y;
	double i = p0.z - p1.z, j = p0.z - p2.z, k = ray.d.z, l = p0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double inv_denom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

	if (beta < 0.0)
		return (false);

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;

	if (gamma < 0.0)
		return (false);

	if (beta + gamma > 1.0)
		return (false);

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

	if (t < kEpsilon)
		return (false);

	tmin = t;

	return(true);
}

Point3D Triangle::get_point() const {
	Point3D answer;
	answer.x = (p0.x + p1.x + p2.x) / 3;
	answer.y = (p0.y + p1.y + p2.y) / 3;
	answer.z = (p0.z + p1.z + p2.z) / 3;
	return answer;
}