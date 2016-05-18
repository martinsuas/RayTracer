/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/

#include "BTDF.h"

BTDF::BTDF(void) {}

BTDF::BTDF(const BTDF& btdf) {}

BTDF::~BTDF(void) {}

BTDF& BTDF::operator= (const BTDF& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}

RGBColor BTDF::f(const ShadeRec& src, const Vector3D& wo, const Vector3D& wi) const {
	return (black);
}

RGBColor BTDF::sample_f(const ShadeRec& src, const Vector3D& wo, Vector3D& wi) const {
	return (black);
}

RGBColor BTDF::rho(const ShadeRec& src, const Vector3D& wo) const {
	return (black);
}

bool BTDF::tir(const ShadeRec& src) const {
	return false;
}