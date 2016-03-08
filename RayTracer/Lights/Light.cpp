#include "Light.h"
#include "../Utilities/Constants.h"

Light::Light(void) {}

Light::Light(const Light& ls) {}

Light&
Light::operator= (const Light& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}

Light::~Light(void) {}

RGBColor
Light::L(ShadeRec& s) {
	return (black);
}

bool
Light::casts_shadows() {
	return false;
}

bool
Light::in_shadow(const Ray &ray, const ShadeRec &sr) const {
	return false;
}