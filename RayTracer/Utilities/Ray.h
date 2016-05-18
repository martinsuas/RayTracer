#pragma once
#include "Point3D.h"
#include "Vector3D.h"

/*
Class used to represent a ray. Public by default due its frequent use.
*/
class Ray {
public:
	Point3D o; // origin
	Vector3D d; // direction

	// Constructors
	Ray(void);
	Ray(const Point3D &origin, const Vector3D &dir);
	Ray(const Ray &ray);
	~Ray(void);
	
	// Operators
	Ray& operator= (const Ray &rhs);
};
