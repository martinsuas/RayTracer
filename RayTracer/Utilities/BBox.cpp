/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include "BBox.h"
#include "Constants.h"
#include <algorithm>
#include <iostream>
BBox::BBox() //:
	//p1(Point3D()),
	//p2(Point3D())
{}

BBox::BBox(const BBox &box) :
	p1(box.p1),
	p2(box.p2)
{}

BBox::BBox(const Point3D &p1, const Point3D &p2) :
	p1(p1),
	p2(p2)
{}

BBox::BBox(const double x1, const double y1, const double z1,
	const double x2, const double y2, const double z2) :
	p1(Point3D(x1, y1, z1)),
	p2(Point3D(x2, y2, z2))
{}

BBox::~BBox(void) {}

bool BBox::hit(const Ray& ray) const {
	double minx, miny, minz, maxx, maxy, maxz;

	double a = 1.0 / ray.d.x;
	if (a >= 0) {
		minx = (p1.x - ray.o.x) * a;
		maxx = (p2.x - ray.o.x) * a;
	}
	else {
		minx = (p2.x - ray.o.x) * a;
		maxx = (p1.x - ray.o.x) * a;
	}

	double b = 1.0 / ray.d.y;
	if (b >= 0) {
		miny = (p1.y - ray.o.y) * b;
		maxy = (p2.y - ray.o.y) * b;
	}
	else {
		miny = (p2.y - ray.o.y) * b;
		maxy = (p1.y - ray.o.y) * b;
	}

	double c = 1.0 / ray.d.z;
	if (c >= 0) {
		minz = (p1.z - ray.o.z) * c;
		maxz = (p2.z - ray.o.z) * c;
	}
	else {
		minz = (p2.z - ray.o.z) * c;
		maxz = (p1.z - ray.o.z) * c;
	}

	double t1, t2;
	if (minx > miny)
		t1 = minx;
	else
		t1 = miny;

	if (minz > t1)
		t1 = minz;

	if (maxx < maxy)
		t2 = maxx;
	else
		t2 = maxy;

	if (maxz < t2)
		t2 = maxz;

	return (t1 < t2 && t2 > kEpsilon);
}

bool BBox::in(const Point3D &p) const {
	return (p1.x < p.x && p.x < p2.x) && (p1.y  < p.y && p.y < p2.y)
		&& (p1.z  < p.z && p.z < p2.z);
}

void BBox::expand(const BBox &bbox) {

	p1.x = std::min(p1.x, bbox.p1.x);
	p1.y = std::min(p1.y, bbox.p1.y);
	p1.z = std::min(p1.z, bbox.p1.z);
	p2.x = std::max(p2.x, bbox.p2.x);
	p2.y = std::max(p2.y, bbox.p2.y);
	p2.z = std::max(p2.z, bbox.p2.z);

}

int BBox::longest_axis() const {
	Vector3D dis = p2 - p1;
	double xdef = abs(dis.x);//p2.x - p1.x);
	double ydef = abs(dis.y);//p2.y - p1.y);
	double zdef = abs(dis.z);//p2.z - p1.z);
	if (xdef >= ydef && xdef >= zdef)
		return 1;
	else if (ydef >= xdef && ydef >= zdef)
		return 2;
	else
		return 3;
}