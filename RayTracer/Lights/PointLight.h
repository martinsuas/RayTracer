#pragma once
#include "Light.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/RGBColor.h"

#include "../World/World.h"			// you will need this later on for shadows
#include "../Utilities/ShadeRec.h"

class PointLight : public Light {
public:
	PointLight(void);
	PointLight(const PointLight& dl);
	virtual Light*
		clone(void) const;
	PointLight&
		operator= (const PointLight& rhs);
	virtual
		~PointLight(void);
	void
		scale_radiance(const float b);
	void
		set_color(const float c);
	void
		set_color(const RGBColor& c);
	void
		set_color(const float r, const float g, const float b);
	void
		set_point(const Point3D &p);
	void
		set_point(const float x, const float y, const float z);
	void
		set_point(const float c);

	virtual Vector3D
		get_direction(ShadeRec& sr);

	virtual bool casts_shadows();

	virtual RGBColor
		L(ShadeRec& sr);
	virtual bool
		in_shadow(const Ray &ray, const ShadeRec &sr) const;

private:
	float ls;
	RGBColor color;
	Point3D point;
};

// Inline function 
inline void
PointLight::scale_radiance(const float b) {
	ls = b;
}

inline void
PointLight::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}

inline void
PointLight::set_color(const RGBColor& c) {
	color = c;
}

inline void
PointLight::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

inline void
PointLight::set_point(const Point3D &p) {
	point = p;
}

inline void
PointLight::set_point(const float x, const float y, const float z) {
	point.x = x; point.y = y; point.z = z;
}

inline void
PointLight::set_point(const float c) {
	point = c;
}