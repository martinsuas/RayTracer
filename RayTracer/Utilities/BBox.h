#pragma once
#include "Point3D.h"
#include "Ray.h"

class BBox
{
public:
	BBox(void);
	BBox(const double x0, const double x1,
		const double y0, const double y1,
		const double z0, const double z1);
	BBox(const Point3D& p0, const Point3D& p1);
	BBox(const BBox& bbox);
	BBox& operator=(const BBox& bbox);
	virtual ~BBox(void);

	bool hit(const Ray& ray) const;
	bool inside(const Point3D& p) const;

public:
	double x0;
	double x1;
	double y0;
	double y1;
	double z0;
	double z1;
};