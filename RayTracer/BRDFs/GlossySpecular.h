/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "BRDF.h"

class GlossySpecular : public BRDF {
public:
	// Constructors
	GlossySpecular(void);

	GlossySpecular(const GlossySpecular& lamb);

	virtual GlossySpecular*
		clone(void) const;

	~GlossySpecular(void);

	// Operators
	GlossySpecular& operator= (const GlossySpecular& rhs);

	// Functions
	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

	void set_ka(const float ka);
	void set_ks(const float kd);
	void set_cs(const RGBColor& c);
	void set_cs(const float r, const float g, const float b);
	void set_cs(const float c);
	void set_exp(const float exp);

private:

	float		ks;
	RGBColor 	cs;
	float		exp;
};
// Inline functions
inline void GlossySpecular::set_ka(const float k) {
	ks = k;
}

inline void GlossySpecular::set_ks(const float k) {
	ks = k;
}

inline void GlossySpecular::set_cs(const RGBColor& c) {
	cs = c;
}

inline void GlossySpecular::set_cs(const float r, const float g, const float b) {
	cs.r = r; cs.g = g; cs.b = b;
}

inline void GlossySpecular::set_cs(const float c) {
	cs.r = c; cs.g = c; cs.b = c;
}

inline void GlossySpecular::set_exp(const float e) {
	exp = e;
}