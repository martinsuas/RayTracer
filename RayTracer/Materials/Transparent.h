/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "Phong.h"
#include "../BTDF/PerfectTransmitter.h"
#include "../BRDFs/PerfectSpecular.h"

class Transparent : public Phong {

public:
	Transparent(void);
	Transparent(const Transparent& r);
	virtual Transparent* clone(void) const;
	Transparent& operator= (const Transparent& rhs);
	virtual ~Transparent(void);

	void set_ior(const float i);
	void set_kr(const float k);
	void set_kt(const float k);

	virtual RGBColor shade(ShadeRec& sr);
	virtual RGBColor area_light_shade(ShadeRec& sr);

private:
	PerfectSpecular* reflective_brdf;
	PerfectTransmitter* specular_btdf;
};

inline void Transparent::set_ior(const float i) {
	specular_btdf->set_ior(i);
}

inline void Transparent::set_kr(const float k) {
	reflective_brdf->set_kr(k);
}

inline void Transparent::set_kt(const float k) {
	specular_btdf->set_kt(k);
}