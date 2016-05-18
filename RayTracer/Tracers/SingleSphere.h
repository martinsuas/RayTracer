/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "../Tracers/Tracer.h"

class SingleSphere : public Tracer {
public:
	SingleSphere(void);
	SingleSphere(World* _worldPtr);
	virtual ~SingleSphere(void);
	virtual RGBColor trace_ray(const Ray &ray) const;
};