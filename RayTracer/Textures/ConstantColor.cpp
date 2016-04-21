#include "ConstantColor.h"


ConstantColor::ConstantColor() {}
ConstantColor::~ConstantColor() {}

RGBColor ConstantColor::get_color(const ShadeRec& sr) const {
	return color;
}