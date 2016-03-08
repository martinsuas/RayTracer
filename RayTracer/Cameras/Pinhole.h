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
	float d;	// view/plane distance
	float zoom; // zoom factor
};