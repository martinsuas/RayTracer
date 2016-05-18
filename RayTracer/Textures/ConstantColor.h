/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "Texture.h"

class ConstantColor : public Texture {
public:
	ConstantColor();
	ConstantColor(RGBColor color);
	~ConstantColor();

	virtual ConstantColor* clone(void) const;
	void set_color(const RGBColor& c);
	virtual RGBColor get_color(const ShadeRec& sr) const;

private:
	RGBColor color;
};