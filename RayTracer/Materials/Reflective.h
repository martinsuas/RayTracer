/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "Phong.h"
#include "../BRDFs/PerfectSpecular.h"

class Reflective : public Phong {
public:

	Reflective(void);

	Reflective(const Reflective& rm);

	Reflective& operator= (const Reflective& rhs);

	virtual Reflective* clone(void) const;

	~Reflective(void);

	void set_kr(const float k);

	void set_cr(const RGBColor& c);

	void set_cr(const float r, const float g, const float b);

	void set_cr(const float c);

	virtual RGBColor shade(ShadeRec& s);

private:
	PerfectSpecular* reflective_brdf;
};

inline void
Reflective::set_kr(const float k) {
	reflective_brdf->set_kr(k);
}

inline void
Reflective::set_cr(const RGBColor& c) {
	reflective_brdf->set_cr(c);

}

inline void
Reflective::set_cr(const float r, const float g, const float b) {
	reflective_brdf->set_cr(r, g, b);
}

inline void
Reflective::set_cr(const float c) {
	reflective_brdf->set_cr(c);
}