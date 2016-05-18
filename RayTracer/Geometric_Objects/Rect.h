/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once

#include "GeometricObject.h"
#include "../Utilities/BBox.h"

class Rect : public GeometricObject {
public:
	Rect(void);
	Rect(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b);
	Rect(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n);
	virtual Rect* clone(void) const;
	Rect(const Rect& r);
	virtual ~Rect(void);
	Rect& operator= (const Rect& rhs);

	BBox get_bounding_box(void) const;
	Point3D get_point() const;

	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;
	virtual bool shadow_hit(const Ray& ray, double& tmin) const;

	virtual Normal get_normal(const Point3D& p);
	virtual float pdf(ShadeRec& sr);

private:
	Point3D 		p0;
	Vector3D		a;
	Vector3D		b;
	double			a_len_squared;
	double			b_len_squared;

	float			area;
	float			inv_area; 
	Normal			normal;

	static const double kEpsilon;
};