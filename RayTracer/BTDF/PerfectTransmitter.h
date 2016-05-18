/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "BTDF.h"

class PerfectTransmitter : public BTDF {
public:

	PerfectTransmitter(void);

	PerfectTransmitter(const PerfectTransmitter& pt);

	virtual PerfectTransmitter*
		clone(void);

	~PerfectTransmitter(void);

	PerfectTransmitter& operator= (const PerfectTransmitter& rhs);

	void set_kt(const float k);

	void set_ior(const float eta);

	bool tir(const ShadeRec& sr) const;

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

private:

	float	kt;	// transmission coef
	float	ior; // index of ref
};

inline void PerfectTransmitter::set_kt(const float k) {
	kt = k;
}

inline void PerfectTransmitter::set_ior(const float eta) {
	ior = eta;
}