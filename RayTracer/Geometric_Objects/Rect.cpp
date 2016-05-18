/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include "Rect.h"
#include "../Utilities/Maths.h"
#include "../Materials/Material.h"

const double Rect::kEpsilon = 0.0001;

Rect::Rect(void) :
	GeometricObject(),
	p0(-1, 0, -1),
	a(0, 0, 2),
	b(2, 0, 0),
	a_len_squared(4.0),
	b_len_squared(4.0),
	area(4.0),
	inv_area(0.25),
	normal(0, 1, 0) {
}

Rect::Rect(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b) :
	GeometricObject(),
	p0(_p0),
	a(_a),
	b(_b),
	a_len_squared(a.len_squared()),
	b_len_squared(b.len_squared()),
	area(a.length() * b.length()),
	inv_area(1.0 / area)
{
	normal = a ^ b;
	normal.normalize();
}

Rect::Rect(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n) :
	GeometricObject(),
	p0(_p0),
	a(_a),
	b(_b),
	a_len_squared(a.len_squared()),
	b_len_squared(b.len_squared()),
	area(a.length() * b.length()),
	inv_area(1.0 / area),
	normal(n) {
	normal.normalize();
}

Rect* Rect::clone(void) const {
	return (new Rect(*this));
}

Rect::Rect(const Rect& r) :
	GeometricObject(r),
	p0(r.p0),
	a(r.a),
	b(r.b),
	a_len_squared(r.a_len_squared),
	b_len_squared(r.b_len_squared),
	area(r.area),
	inv_area(r.inv_area),
	normal(r.normal) {
}

Rect& Rect::operator= (const Rect& rhs) {
	if (this == &rhs)
		return *this;

	GeometricObject::operator=(rhs);

	p0 = rhs.p0;
	a = rhs.a;
	b = rhs.b;
	a_len_squared = rhs.a_len_squared;
	b_len_squared = rhs.b_len_squared;
	area = rhs.area;
	inv_area = rhs.inv_area;
	normal = rhs.normal;

	return *this;
}

Rect::~Rect(void) {
	delete material_ptr;
}

BBox Rect::get_bounding_box(void) const {
	double off = 0.0001;

	return BBox(
		min(p0.x, p0.x + a.x + b.x) - off,
		min(p0.y, p0.y + a.y + b.y) - off,
		min(p0.z, p0.z + a.z + b.z) - off,
		max(p0.x, p0.x + a.x + b.x) + off,
		max(p0.y, p0.y + a.y + b.y) + off,
		max(p0.z, p0.z + a.z + b.z) + off);
} 

bool Rect::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double t = (p0 - ray.o) * normal / (ray.d * normal);

	if (t <= kEpsilon)
		return false;

	Point3D p = ray.o + t * ray.d;
	Vector3D d = p - p0;

	double ddota = d * a;

	if (ddota < 0.0 || ddota > a_len_squared)
		return false;

	double ddotb = d * b;

	if (ddotb < 0.0 || ddotb > b_len_squared)
		return false;

	tmin = t;
	sr.normal = normal;
	sr.local_hit_point = p;

	return true;
}


bool Rect::shadow_hit(const Ray& ray, double& tmin) const {
	double t = (p0 - ray.o) * normal / (ray.d * normal);

	if (t <= kEpsilon)
		return false;

	Point3D p = ray.o + t * ray.d;
	Vector3D d = p - p0;

	double ddota = d * a;

	if (ddota < 0.0 || ddota > a_len_squared)
		return false;

	double ddotb = d * b;

	if (ddotb < 0.0 || ddotb > b_len_squared)
		return false;

	tmin = t;
	return true;
}
 
Normal Rect::get_normal(const Point3D& p) {
	return normal;
}

float Rect::pdf(ShadeRec& sr) {
	return inv_area;
}

Point3D Rect::get_point() const {
	return p0;
}