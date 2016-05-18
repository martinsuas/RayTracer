#pragma once
/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once

#include "GeometricObject.h"
#include "../Utilities/BBox.h"

class Triangle : public GeometricObject {
public:
	Triangle(void);
	Triangle(const Point3D& _a, const Point3D& _b, const Point3D& _c);
	virtual Triangle* clone(void) const;
	Triangle(const Triangle& t);
	virtual ~Triangle(void);
	Triangle& operator= (const Triangle& rhs);

	BBox get_bounding_box(void) const;
	Point3D get_point() const;

	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;
	virtual bool shadow_hit(const Ray& ray, double& tmin) const;
	

private:
	Point3D		p0;
	Point3D		p1;
	Point3D		p2;
	Normal			normal;
};