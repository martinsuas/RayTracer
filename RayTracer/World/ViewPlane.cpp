#include "ViewPlane.h"

ViewPlane::ViewPlane(void)
	:	hres(400), vres(400), s(1.0), num_samples(4),
		gamma(1.0), inv_gamma(1.0) {}

ViewPlane::ViewPlane(const ViewPlane &vp)
	:	hres(vp.hres), vres(vp.vres), s(vp.s), num_samples(vp.num_samples),
		gamma(vp.gamma), inv_gamma(vp.inv_gamma) {}

//book
ViewPlane&
ViewPlane::operator= (const ViewPlane& rhs) {
	if (this == &rhs)
		return (*this);

	hres = rhs.hres;
	vres = rhs.vres;
	s = rhs.s;
	gamma = rhs.gamma;
	inv_gamma = rhs.inv_gamma;

	return (*this);
}
//
ViewPlane::~ViewPlane(void) {}