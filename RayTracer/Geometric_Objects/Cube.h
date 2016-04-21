#pragma once
// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "GeometricObject.h"
#include "../Utilities/BBox.h"

class Cube : public GeometricObject {
public:
	Cube(void);
	Cube(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b);
	Cube(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n);
	virtual Cube* clone(void) const;
	Cube(const Cube& r);
	virtual ~Cube(void);
	Cube& operator= (const Cube& rhs);

	BBox get_bounding_box(void) const;

	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;
	virtual bool shadow_hit(const Ray& ray, double& tmin) const;

	// the following functions are used when the Cube is a light source
	virtual Normal get_normal(const Point3D& p);
	virtual float pdf(ShadeRec& sr);

private:
	Point3D 		p0;   			// corner vertex
	Vector3D		a;				// side
	Vector3D		b;				// side
	double			a_len_squared;	// square of the length of side a
	double			b_len_squared;	// square of the length of side b

	float			area;			// for rectangular lights
	float			inv_area;		// for rectangular lights
	Normal			normal;

	static const double kEpsilon;
};