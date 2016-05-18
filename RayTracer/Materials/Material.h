/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "../World/World.h"	
#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeRec.h"

class Material {
public:

	Material(void);

	Material(const Material& material);

	virtual Material* clone(void) const = 0;

	virtual ~Material(void);

	virtual RGBColor shade(ShadeRec& sr);

protected:

	Material& operator= (const Material& rhs);
};