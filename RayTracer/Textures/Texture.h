/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeRec.h"

class Texture {
public:
	Texture();
	Texture(const Texture& texture);
	virtual Texture* clone(void) const = 0;
	virtual ~Texture();

	virtual RGBColor get_color(const ShadeRec& sr) const = 0;
protected:
	Texture& operator= (const Texture& rhs);
};