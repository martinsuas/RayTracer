/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once

class Material;

#include "../Utilities/Point3D.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/BBox.h"

//Represents an object in the 3D world.
class GeometricObject {
public:
	// Constructors 
	GeometricObject(void);
	GeometricObject(const GeometricObject& object);
	virtual ~GeometricObject(void);

	virtual GeometricObject* clone(void) const = 0;

	// Getters
	Material* get_material(void) const;
	RGBColor get_color(void) const;

	// Setters
	virtual void set_material(Material *material_ptr);
	virtual void set_color(float r, float g, float b);

	// Functions
	virtual BBox get_bounding_box(void) const = 0;
	virtual bool hit(const Ray &ray, double &tmin, ShadeRec &sr) const = 0; // pure virtual
	virtual bool shadow_hit(const Ray &ray, double &tmin) const = 0;
	virtual Point3D get_point() const = 0;
protected:
	mutable Material* material_ptr;
	RGBColor color;
	GeometricObject& operator= (const GeometricObject& rhs);
};

inline Material* GeometricObject::get_material(void) const {
	return (material_ptr);
}

inline RGBColor GeometricObject::get_color(void) const {
	return (color);
}
