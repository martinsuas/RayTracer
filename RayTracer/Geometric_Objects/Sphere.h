/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once

#include "GeometricObject.h"
class Sphere : public GeometricObject {
public:
	// Constructors
	Sphere(void);		// Default constructor

	Sphere(const Point3D center, double r); // Constructor

	Sphere(const Sphere &sphere);

	virtual Sphere* clone(void) const;

	virtual ~Sphere(void);

	BBox get_bounding_box(void) const;
	Point3D get_point() const;


	// Operators
	Sphere& operator= (const Sphere &sphere);

	// Operations
	void set_center(const Point3D &c);

	void set_center(const double x, const double y, const double z);

	void set_radius(const double r);

	virtual bool hit(const Ray &ray, double &t, ShadeRec &sr) const;
	virtual bool shadow_hit(const Ray &ray, double &t) const;
private:
	Point3D					center;	  // Location of the center of the sphere.
	double					radius;   // Radius of the sphere
	static const double		kEpsilon; 
};

// Inline functions
inline void Sphere::set_center(const Point3D& c) {
	center = c;
}

inline void Sphere::set_center(const double x, const double y, const double z) {
	center.x = x;
	center.y = y;
	center.z = z;
}

inline void Sphere::set_radius(const double r) {
	radius = r;
}