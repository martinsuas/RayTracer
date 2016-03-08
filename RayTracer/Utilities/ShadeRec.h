#pragma once
#include <vector>

class Material;
class World;

#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "RGBColor.h"

class ShadeRec {
public:
	bool		hit_an_object;		// Checks if ray hitted an object
	Material*	material_ptr;	// Nearest object's material
	Point3D		hit_point;			// World coordinates of hit point
	Point3D		local_hit_point;	// (text?)World coordinates of hit point
	Normal		normal;				// Normal of hit point
	RGBColor	color;				// Chapter 3 only
	Ray			ray;				// For specular highlights
	float		t;					// Ray parameter
	int			depth;				// Recursion depth
	Vector3D	dir;				// Direction of area lights
	World		&w;					// World reference (used for shading)

	ShadeRec(World &wr);			// Constructor
	ShadeRec(const ShadeRec &sr);	// Copy Constructor
};