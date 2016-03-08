#pragma once

class Material;

#include "../Utilities/Point3D.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"

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

	// Setters
	virtual void set_material(Material *material_ptr);

	// Functions
	virtual bool hit(const Ray &ray, double &tmin, ShadeRec &sr) const = 0; // pure virtual
	virtual bool shadow_hit(const Ray &ray, double &tmin) const = 0;
protected:
	mutable Material* material_ptr;
	GeometricObject& operator= (const GeometricObject& rhs);
};

inline Material* GeometricObject::get_material(void) const {
	return (material_ptr);
}
