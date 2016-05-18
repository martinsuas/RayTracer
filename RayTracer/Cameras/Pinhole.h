/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once

#include "../Utilities/Point2D.h"
#include "../World/World.h"
class Pinhole : public Camera {
public:
	// Constructors
	Pinhole();
	Pinhole(const Pinhole &cam);
	~Pinhole();

	// Operator
	Pinhole& operator= (const Pinhole &o);
	// Functions
	Vector3D ray_direction(const Point2D &p) const;
	virtual void render_scene(const World &w);

private:
	float d;	// view distance
	float zoom; // zoom
};