/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include "ConstantColor.h"


ConstantColor::ConstantColor() {}

ConstantColor::ConstantColor(RGBColor _color) {
	color = _color;
}
ConstantColor::~ConstantColor() {}

ConstantColor* ConstantColor::clone(void) const {
	return new ConstantColor(*this);
}

RGBColor ConstantColor::get_color(const ShadeRec& sr) const {
	return color;
}

void ConstantColor::set_color(const RGBColor &col) {
	color = col;
}