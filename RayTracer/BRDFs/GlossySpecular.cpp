#include "GlossySpecular.h"
#include "../Utilities/Constants.h"

GlossySpecular::GlossySpecular(void)
	: BRDF(),
	ks(0.25),
	cs(0.8),
	exp(10)
{}

GlossySpecular::GlossySpecular(const GlossySpecular& lamb)
	: BRDF(lamb),
	ks(lamb.ks),
	cs(lamb.cs)
{}

GlossySpecular*
GlossySpecular::clone(void) const {
	return (new GlossySpecular(*this));
}

GlossySpecular::~GlossySpecular(void) {}

GlossySpecular&
GlossySpecular::operator= (const GlossySpecular& rhs) {
	if (this == &rhs)
		return (*this);

	BRDF::operator= (rhs);

	ks = rhs.ks;
	cs = rhs.cs;

	return (*this);
}

RGBColor
GlossySpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	RGBColor L;
	float ndotwi = sr.normal * wi;
	Vector3D r(-wi + 2.0 * sr.normal * ndotwi);
	float rdotwo = r * wo;
	if (rdotwo > 0.0)
		L = ks * pow(rdotwo, exp);
	return L;
}

RGBColor
GlossySpecular::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return black;
}