/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include "RayCast.h"
#include "../World/World.h"
#include "../Utilities/ShadeRec.h"
#include "../Materials/Material.h"

RayCast::RayCast(void)
	: Tracer()
{}

RayCast::RayCast(World* _worldPtr)
	: Tracer(_worldPtr)
{}

RayCast::~RayCast(void) {}

RGBColor
RayCast::trace_ray(const Ray& ray) const {
	ShadeRec sr(world_ptr->hit_objects(ray));

	if (sr.hit_an_object) {
		sr.ray = ray;
		return (sr.material_ptr->shade(sr));
	}
	else
		return (world_ptr->background_color);
}


RGBColor
RayCast::trace_ray(const Ray ray, const int depth) const {
	ShadeRec sr(world_ptr->hit_objects(ray));

	if (sr.hit_an_object) {
		sr.ray = ray; 
		return (sr.material_ptr->shade(sr));
	}
	else
		return (world_ptr->background_color);
}
