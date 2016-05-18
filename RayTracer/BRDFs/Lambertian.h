/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "BRDF.h"

class Lambertian : public BRDF {
public:
	// Constructors
	Lambertian(void);

	Lambertian(const Lambertian& lamb);

	virtual Lambertian* clone(void) const;

	~Lambertian(void);

	// Operators
	Lambertian& operator= (const Lambertian& rhs);

	// Functions
	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

	void set_ka(const float ka);

	void set_kd(const float kd);

	void set_cd(const RGBColor& c);

	void set_cd(const float r, const float g, const float b);

	void set_cd(const float c);

private:

	float		kd;
	RGBColor 	cd;
};
// Inline functions
inline void Lambertian::set_ka(const float k) {
	kd = k;
}

inline void Lambertian::set_kd(const float k) {
	kd = k;
}

inline void Lambertian::set_cd(const RGBColor& c) {
	cd = c;
}

inline void Lambertian::set_cd(const float r, const float g, const float b) {
	cd.r = r; cd.g = g; cd.b = b;
}

inline void Lambertian::set_cd(const float c) {
	cd.r = c; cd.g = c; cd.b = c;
}