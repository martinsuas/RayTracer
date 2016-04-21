#include "PerfectSpecular.h"

PerfectSpecular::PerfectSpecular(void)
	: BRDF(),
	kr(0.0),
	cr(1.0)
{}

PerfectSpecular::~PerfectSpecular(void) {}

PerfectSpecular*
PerfectSpecular::clone(void) const {
	return (new PerfectSpecular(*this));
}


RGBColor
PerfectSpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	return (black);
}

RGBColor
PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const {

	float ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo;
	return (kr * cr / fabs(sr.normal * wi));
}


RGBColor
PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {

	float ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo;
	pdf = fabs(sr.normal * wi);
	return (kr * cr);
}

RGBColor
PerfectSpecular::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (black);
}