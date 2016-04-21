#include "Texture.h"

Texture::Texture() {}
Texture::~Texture() {}
Texture::Texture(const Texture& /*texture*/) {}

Texture& Texture::operator= (const Texture& rhs) {
	if (this == &rhs)
		return *this;

	return *this;
}