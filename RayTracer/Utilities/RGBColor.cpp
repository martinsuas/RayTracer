/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include "RGBColor.h"
#include <math.h>
// Constructors
RGBColor::RGBColor(void) : r(0.0), g(0.0), b(0.0) {}
RGBColor::RGBColor(float c) : r(c), g(c), b(c) {}

RGBColor::RGBColor(float r, float g, float b)
	: r(r), g(g), b(b) {}

RGBColor::RGBColor(const RGBColor &c)
	: r(c.r), g(c.g), b(c.b) {}

RGBColor::~RGBColor(void) {}

RGBColor& RGBColor::operator= (const RGBColor& rhs) {
	if (this == &rhs)
		return (*this);

	r = rhs.r; g = rhs.g; b = rhs.b;

	return (*this);
}

RGBColor RGBColor::powc(float p) const {
	return (RGBColor(pow(r, p), pow(g, p), pow(b, p)));
}

