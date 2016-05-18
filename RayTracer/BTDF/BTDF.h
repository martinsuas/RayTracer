/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include <math.h>

#include "../Utilities/Constants.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/ShadeRec.h"

class BTDF {
public:

	BTDF(void);

	BTDF(const BTDF& btdf);

	virtual BTDF* clone(void) = 0;

	BTDF& operator= (const BTDF& rhs);

	virtual ~BTDF(void);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

	virtual bool tir(const ShadeRec& sr) const;

};
