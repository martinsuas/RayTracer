#include "MultipleObjects.h"
#include "../World/World.h"

// Constructors
MultipleObjects::MultipleObjects(void) : Tracer() {}
MultipleObjects::MultipleObjects(World* _worldPtr) : Tracer(_worldPtr) {}
MultipleObjects::~MultipleObjects(void) {}

RGBColor MultipleObjects::trace_ray(const Ray& ray) const {
	ShadeRec sr(world_ptr->hit_objects(ray)); // sr is a copy

	if (sr.hit_an_object) {
		//std::cout << sr.color.r << std::endl;
		return (sr.color);
	}
	else
		return (world_ptr->background_color);
}

