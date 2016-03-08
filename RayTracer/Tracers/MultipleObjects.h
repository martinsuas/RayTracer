#pragma once
#include "../Tracers/Tracer.h"
class MultipleObjects : public Tracer {
public:
	// Constructors
	MultipleObjects(void);
	MultipleObjects(World* _world_ptr);

	// Virtuals
	virtual ~MultipleObjects(void); 
	virtual RGBColor trace_ray(const Ray& ray) const;
};