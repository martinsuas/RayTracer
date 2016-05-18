/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "Light.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/RGBColor.h"

#include "../World/World.h"
#include "../Utilities/ShadeRec.h"


class Directional : public Light {
public:
	Directional(void);
	Directional(const Directional& dl);
	virtual Light* clone(void) const;
	Directional& operator= (const Directional& rhs);
	virtual ~Directional(void);
	void scale_radiance(const float b);
	void set_color(const float c);
	void set_color(const RGBColor& c);
	void set_color(const float r, const float g, const float b);
	void set_direction(Vector3D d);
	void set_direction(float dx, float dy, float dz);
	virtual Vector3D get_direction(ShadeRec& sr);
	virtual RGBColor L(ShadeRec& sr);

private:
	float		ls;
	RGBColor	color;
	Vector3D	dir;
};


// Inline function 
inline void Directional::scale_radiance(const float b) {
	ls = b;
}

inline void Directional::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}

inline void Directional::set_color(const RGBColor& c) {
	color = c;
}

inline void Directional::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

inline void Directional::set_direction(Vector3D d) {
	dir = d;
	dir.normalize();
}

inline void Directional::set_direction(float dx, float dy, float dz) {
	dir.x = dx; dir.y = dy; dir.z = dz;
	dir.normalize();
}