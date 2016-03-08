#include "Tracer.h"
// Constructors
Tracer::Tracer(void) : world_ptr(NULL) {}
Tracer::Tracer(World* w_ptr) : world_ptr(w_ptr) {}

// Virtuals (overrideable)
Tracer::~Tracer(void) {
	if (world_ptr)
		world_ptr = NULL;
}

RGBColor Tracer::trace_ray(const Ray &ray) const {
	return black;
}

RGBColor Tracer::trace_ray(const Ray ray, const int depth) const {
	return (black);
}
