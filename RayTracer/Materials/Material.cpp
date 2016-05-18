/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include "Material.h"

Material::Material(void) {}

Material::Material(const Material& m) {}

Material& Material::operator= (const Material& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}

Material::~Material(void)
{}

RGBColor Material::shade(ShadeRec& sr) {
	return (black);
}
