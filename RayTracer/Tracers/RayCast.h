/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "Tracer.h"

class RayCast : public Tracer {
public:

	RayCast(void);

	RayCast(World* _worldPtr);

	virtual
		~RayCast(void);

	virtual RGBColor
		trace_ray(const Ray& ray) const;

	virtual RGBColor
		trace_ray(const Ray ray, const int depth) const;
};