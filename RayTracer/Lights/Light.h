#pragma once
#include "../Utilities/Vector3D.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"

class ShadeRec;

class Light {
public:

	Light(void);

	Light(const Light& ls);

	Light&
		operator= (const Light& rhs);

	virtual Light*
		clone(void) const = 0;

	virtual bool
		casts_shadows();

	virtual bool
		in_shadow(const Ray &ray, const ShadeRec &sr) const;

	virtual
		~Light(void);

	virtual Vector3D
		get_direction(ShadeRec& sr) = 0;

	virtual RGBColor
		L(ShadeRec& sr);
};