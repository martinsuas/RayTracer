/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once

#include "Ray.h"
#include "Point3D.h"

class BBox {
public:
	BBox();
	BBox(const BBox &box);
	BBox(const Point3D &p1, const Point3D &p2);
	BBox(const double x1, const double y1, const double z1,
		const double x2, const double y2, const double z2);
	~BBox();

	bool hit(const Ray &r) const;
	bool in(const Point3D &p) const;

	void expand(const BBox &bbox);
	int longest_axis() const;

	Point3D p1;
	Point3D p2;
}; 