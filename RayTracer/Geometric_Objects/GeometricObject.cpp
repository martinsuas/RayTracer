#include "../Utilities/Constants.h"
#include "../Materials/Material.h"
#include "GeometricObject.h"

// Constructors
GeometricObject::GeometricObject(void) : 
	material_ptr(NULL) {}

GeometricObject::GeometricObject(const GeometricObject& object) {
	if (object.material_ptr)
		material_ptr = object.material_ptr->clone();
	else  material_ptr = NULL;
}

GeometricObject& GeometricObject::operator= (const GeometricObject& rhs) {
	if (this == &rhs)
		return (*this);

	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr->clone();

	return (*this);
}

GeometricObject::~GeometricObject(void) {
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
}

// Setters
void GeometricObject::set_material(Material* mPtr) {
	material_ptr = mPtr;
}

void GeometricObject::set_color(float r, float g, float b) {
	color.r = r; color.g = g; color.b = b;
}

