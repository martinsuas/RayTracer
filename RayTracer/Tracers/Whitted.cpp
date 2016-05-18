/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include "Whitted.h"
#include "../World/World.h"
#include "../Utilities/ShadeRec.h"
#include "../Materials/Material.h"

Whitted::Whitted(void)
	: Tracer()
{}


Whitted::Whitted(World* _worldPtr)
	: Tracer(_worldPtr)
{}


Whitted::~Whitted(void) {}

RGBColor
Whitted::trace_ray(const Ray ray, const int depth) const {
	if (depth > world_ptr->vp.max_depth)
		return(black);
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));

		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = ray;
			return (sr.material_ptr->shade(sr));
		}
		else
			return (world_ptr->background_color);
	}
}

RGBColor
Whitted::trace_ray(const Ray& ray) const {
	return trace_ray(ray, 1);
}