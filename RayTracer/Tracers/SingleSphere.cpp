/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include "SingleSphere.h"
#include "../World/World.h"
#include "../Utilities/ShadeRec.h"

SingleSphere::SingleSphere(void) : Tracer() {}
SingleSphere::SingleSphere(World* _worldPtr) : Tracer(_worldPtr){}
SingleSphere::~SingleSphere(void){}

RGBColor SingleSphere::trace_ray(const Ray &ray) const {
	ShadeRec	sr(*world_ptr); // not used yet
	double		t;				// not used yet

	if (world_ptr->sphere.hit(ray, t, sr))
		return red;
	else
		return black;
}