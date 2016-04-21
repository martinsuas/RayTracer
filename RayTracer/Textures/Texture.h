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
	Texture&
		operator= (const Texture& rhs);
};