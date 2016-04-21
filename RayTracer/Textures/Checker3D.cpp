#include "Checker3D.h"
#include <iostream>

Checker3D::Checker3D(void) :
	Texture(),
	size(1.0),
	color1(1.0),
	color2(0.0) {
}

Checker3D::Checker3D(const Checker3D& ch) :
	Texture(ch),
	size(ch.size),
	color1(ch.color1),
	color2(ch.color2) {
}

Checker3D& Checker3D::operator= (const Checker3D& rhs) {
	if (this == &rhs)
		return *this;

	Texture::operator=(rhs);

	size = rhs.size;
	color1 = rhs.color1;
	color2 = rhs.color2;

	return *this;
}

Checker3D* Checker3D::clone(void) const {
	return new Checker3D(*this);
}

Checker3D::~Checker3D(void) {
}

RGBColor Checker3D::get_color(const ShadeRec& sr) const {

	float eps = -0.0001753567;
	float x = sr.local_hit_point.x + eps;
	float y = sr.local_hit_point.y + eps;
	float z = sr.local_hit_point.z + eps;

	if (((int)floor(x / size) + (int)floor(y / size) + (int)floor(z / size)) % 2 == 0) {
		return (color1);
	}
	else {
		return (color2);
	}
	// Debug - move befroe if to use
	if (x > 1 || y > 1 || z > 1) {
		std::cout << (x) << std::endl;
		std::cout << (y) << std::endl;
		std::cout << (z) << std::endl;
	}
}