#include "SV_Lambertian.h"
#include "../Utilities/Constants.h"

SV_Lambertian::SV_Lambertian():
	BRDF(),
	kd(0.0),
	cd(NULL)
{}

SV_Lambertian::SV_Lambertian(const SV_Lambertian& lamb) :
	BRDF(lamb),
	kd(lamb.kd) {
	if (lamb.cd)
		cd = lamb.cd->clone();
	else
		cd = NULL;
}

SV_Lambertian* SV_Lambertian::clone(void) const {
	return new SV_Lambertian(*this);
}

SV_Lambertian::~SV_Lambertian() {
	delete cd;
}

SV_Lambertian& SV_Lambertian::operator= (const SV_Lambertian& rhs) {
	if (this == &rhs)
		return *this;

	BRDF::operator= (rhs);

	kd = rhs.kd;

	if (cd) {
		delete cd;
		cd = NULL;
	}

	if (rhs.cd)
		cd = rhs.cd->clone();

	return *this;
}

RGBColor SV_Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (kd * cd->get_color(sr));
}

RGBColor SV_Lambertian::f(const ShadeRec& sr, const Vector3D& wo,
	const Vector3D& wi) const {
	return (kd * cd->get_color(sr) * invPI);
}
