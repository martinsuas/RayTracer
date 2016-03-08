#include "PointLight.h"

PointLight::PointLight(void)
	: Light(),
	ls(1.0),
	color(1.0),
	point(0,0,0)
{}

PointLight::PointLight(const PointLight& dl)
	: Light(dl),
	ls(dl.ls),
	color(dl.color),
	point(dl.point)
{}

Light*
PointLight::clone(void) const {
	return (new PointLight(*this));
}

PointLight&
PointLight::operator= (const PointLight& rhs)
{
	if (this == &rhs)
		return (*this);

	Light::operator= (rhs);

	ls = rhs.ls;
	color = rhs.color;
	point = rhs.point;

	return (*this);
}

PointLight::~PointLight(void) {}

Vector3D
PointLight::get_direction(ShadeRec& sr) {
	return (point - sr.hit_point).hat();
}

bool
PointLight::casts_shadows() {
	return true;
}

RGBColor
PointLight::L(ShadeRec& s) {
	return (ls * color);
}

bool
PointLight::in_shadow(const Ray &ray, const ShadeRec &sr) const {
	double t;
	int num_objects = sr.w.objects.size();
	float d = point.distance(ray.o);

	for (int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
			return true;
	return false;
}
