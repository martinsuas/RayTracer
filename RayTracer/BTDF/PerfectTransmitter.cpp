/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include "PerfectTransmitter.h"

PerfectTransmitter::PerfectTransmitter(void)
	: BTDF(),
	kt(0.0),
	ior(1.0)
{}

PerfectTransmitter::PerfectTransmitter(const PerfectTransmitter& pt)
	: BTDF(pt),
	kt(pt.kt),
	ior(pt.ior)
{}

PerfectTransmitter* PerfectTransmitter::clone(void) {
	return (new PerfectTransmitter(*this));
}

PerfectTransmitter::~PerfectTransmitter(void) {}

PerfectTransmitter& PerfectTransmitter::operator= (const PerfectTransmitter& rhs) {
	if (this == &rhs)
		return (*this);

	kt = rhs.kt;
	ior = rhs.ior;

	return (*this);
}

bool PerfectTransmitter::tir(const ShadeRec& sr) const {
	Vector3D wo(-sr.ray.d);
	float cos_thetai = sr.normal * wo;
	float eta = ior;

	if (cos_thetai < 0.0)
		eta = 1.0 / eta;

	return (1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta) < 0.0);
}

RGBColor PerfectTransmitter::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	return (black);
}

RGBColor PerfectTransmitter::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const {

	Normal n(sr.normal);
	float cos_thetai = n * wo;
	float eta = ior;

	if (cos_thetai < 0.0) {	// outside
		cos_thetai = -cos_thetai;
		n = -n;  
		eta = 1.0 / eta; 		
	}

	float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
	float cos_theta2 = sqrt(temp);
	wt = -wo / eta - (cos_theta2 - cos_thetai / eta) * n;

	return (kt / (eta * eta) * white / fabs(sr.normal * wt));
}



RGBColor PerfectTransmitter::rho(const ShadeRec& src, const Vector3D& wo) const {
	return (black);
}

