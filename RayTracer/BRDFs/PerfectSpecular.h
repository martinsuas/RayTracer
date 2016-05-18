/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once

#include "BRDF.h"
#include "../Utilities/Normal.h"
#include "../Utilities/Constants.h"

class PerfectSpecular : public BRDF {

public:

	PerfectSpecular(void);

	~PerfectSpecular(void);

	virtual PerfectSpecular* clone(void) const;

	void set_kr(const float k);

	void set_cr(const RGBColor& c);

	void set_cr(const float r, const float g, const float b);

	void set_cr(const float c);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

private:
	float		kr;	
	RGBColor 	cr;
};

inline void PerfectSpecular::set_kr(const float k) {
	kr = k;
}

inline void PerfectSpecular::set_cr(const RGBColor& c) {
	cr = c;
}


inline void PerfectSpecular::set_cr(const float r, const float g, const float b) {
	cr.r = r; cr.g = g; cr.b = b;
}

inline void PerfectSpecular::set_cr(const float c) {
	cr.r = c; cr.g = c; cr.b = c;
}