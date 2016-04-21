#pragma once
#include "Texture.h"

class ConstantColor : public Texture {
public:
	ConstantColor();
	~ConstantColor();

	void set_color(const RGBColor& c);
	virtual RGBColor get_color(const ShadeRec& sr) const;

private:
	RGBColor color;
};