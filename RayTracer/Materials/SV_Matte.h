/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "Material.h"
#include "../Textures/Texture.h"
#include "../BRDFs/SV_Lambertian.h"
class SV_Matte : public Material {
public:
	SV_Matte();
	SV_Matte(const SV_Matte& m);
	SV_Matte& operator=(const SV_Matte& rhs);
	~SV_Matte();

	virtual Material* clone(void) const;

	void set_cd(Texture* t_ptr);
	void set_ka(const float ka);
	void set_kd(const float k);

	virtual RGBColor shade(ShadeRec& s);

private:
	SV_Lambertian* ambient_brdf;
	SV_Lambertian* diffuse_brdf;
};

inline void SV_Matte::set_cd(Texture* t_ptr) {
	ambient_brdf->set_cd(t_ptr);
	diffuse_brdf->set_cd(t_ptr);
}

inline void
SV_Matte::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}

inline void
SV_Matte::set_kd(const float kd) {
	diffuse_brdf->set_kd(kd);
}