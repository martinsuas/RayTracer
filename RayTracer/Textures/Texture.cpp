/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include "Texture.h"

Texture::Texture() {}
Texture::~Texture() {}
Texture::Texture(const Texture& texture) {}

Texture& Texture::operator= (const Texture& rhs) {
	if (this == &rhs)
		return *this;

	return *this;
}