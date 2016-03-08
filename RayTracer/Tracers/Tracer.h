#pragma once
#include "../Utilities/Constants.h"
#include "../Utilities/Ray.h"
#include "../Utilities/RGBColor.h"

class World;
/*
Base class used to represent all the tracers. All of them take a world pointer.
*/
class Tracer {
public:
	// Constructors
	Tracer(void);
	Tracer(World* _w_ptr);

	//Virtuals
	virtual ~Tracer(void);
	virtual RGBColor trace_ray(const Ray &ray) const;
	virtual RGBColor trace_ray(const Ray ray, const int depth) const;
	//virtual RGBColor trace_ray(const Ray ray, float &tmin, const int depth) const;

protected:
	World* world_ptr;
};