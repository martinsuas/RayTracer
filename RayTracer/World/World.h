#pragma once
#include <vector>

#include "ViewPlane.h"
#include "../Utilities/RGBColor.h"
#include "../Tracers/Tracer.h"
#include "../Geometric_Objects/GeometricObject.h"
#include "../Geometric_Objects/Sphere.h"
#include "../Geometric_Objects/Plane.h"
#include "../Utilities/Ray.h"

#include "../Lights/Light.h"
#include "../Cameras/Camera.h"
#include "../Lights/Ambient.h"

using namespace std;

class World {
public:
	ViewPlane					vp;
	RGBColor					background_color;
	Light						*ambient_ptr;
	Tracer						*tracer_ptr;
	Camera						*camera_ptr;
	Sphere						sphere;
	vector<Light*>				lights;
	vector<GeometricObject*>	objects;

public:
	World(void);	// Default constructor

	void build(void);

	void add_object(GeometricObject* object_ptr);

	void add_light(Light* light_ptr);

	void set_camera(Camera* c_ptr);
	void set_ambient_light(Light* light_ptr);

	ShadeRec hit_objects(const Ray &ray);

	//void render_scene(void) const;

	//void open_window(const int hres, const int vres) const;

	//void display_pixel(const int row, const int column,
	//	const RGBColor &pixel_color) const;
};

// Inline functions
inline void World::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}

inline void World::add_light(Light* light_ptr) {
	lights.push_back(light_ptr);
}
inline void World::set_camera(Camera* c_ptr) {
	camera_ptr = c_ptr;
}

inline void World::set_ambient_light(Light* light_ptr) {
	ambient_ptr = light_ptr;
}