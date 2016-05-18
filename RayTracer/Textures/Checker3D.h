/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "Texture.h" 
class Checker3D : public Texture {
public:
	Checker3D(void);
	Checker3D(const Checker3D& ch);
	Checker3D& operator= (const Checker3D& rhs);
	virtual Checker3D* clone(void) const;
	virtual ~Checker3D(void);

	virtual RGBColor get_color(const ShadeRec& sr) const;

	void set_size(const float s);
	void set_color1(const RGBColor& c);
	void set_color1(const float r, const float g, const float b);
	void set_color1(const float c);
	void set_color2(const RGBColor& c);
	void set_color2(const float r, const float g, const float b);
	void set_color2(const float c);

private:
	float size;
	RGBColor color1;
	RGBColor color2;
};

inline void Checker3D::set_size(const float s) {
	size = s;
}

inline void Checker3D::set_color1(const RGBColor& c) {
	color1 = c;
}

inline void Checker3D::set_color1(const float c) {
	color1.r = c;
	color1.g = c;
	color1.b = c;
}

inline void Checker3D::set_color1(const float r, const float g, const float b) {
	color1.r = r;
	color1.g = g;
	color1.b = b;
}

inline void Checker3D::set_color2(const RGBColor& c) {
	color2 = c;
}

inline void Checker3D::set_color2(const float c) {
	color2.r = c;
	color2.g = c;
	color2.b = c;
}

inline void Checker3D::set_color2(const float r, const float g, const float b) {
	color2.r = r;
	color2.g = g;
	color2.b = b;
}