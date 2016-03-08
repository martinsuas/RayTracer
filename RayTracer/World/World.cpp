#include "World.h"
#include "../Utilities/Constants.h"

// Geometric Objects
#include "../Geometric_Objects/Plane.h"
#include "../Geometric_Objects/Sphere.h"

#include "../Tracers/SingleSphere.h"
#include "../Tracers/MultipleObjects.h"
#include "../Tracers/RayCast.h"

#include "../Cameras/Pinhole.h"

#include "../Lights/Directional.h"
#include "../Lights/PointLight.h"

#include "../Materials/Matte.h"
#include "../Materials/Phong.h"

#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/ShadeRec.h"


// Build Functions
#include <GL/freeglut.h>
#include <iostream>

World::World(void)
	: background_color(black),
	tracer_ptr(NULL),
	camera_ptr(NULL),
	ambient_ptr(new Ambient)
{}

void World::build(void) {
	RGBColor background = black;

	// OpenGL Paramaters
	// Using single buffer, RGB color select
	float width = 400;
	float height = 400;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode.
	glutInitWindowPosition(50, 100); // Set top-left display-window position.
	glutInitWindowSize(width, height); // Set display-window width and height.
	glutCreateWindow("Martin Suarez - Checkpoint 3"); // Create display window.
	glClearColor(background.r, background.g, background.b, 0.0); // Set display-window color to white.
	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	//gluOrtho2D(-width /2.0, width/2.0, -height /2.0, height /2.0);
	gluOrtho2D(0.0, width, 0.0, height);

	// RayTracer Parameters
	vp.set_hres(width);
	vp.set_vres(height);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);

	Ambient *ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr);

	// Camera Parameters
	Pinhole* cam = new Pinhole();
	cam->set_eye(70, 75, 200.0);
	cam->set_lookat(70, 65, -500.0);
	cam->set_up(0.0, 1.0, 0.0); // try -1?
	cam->compute_ortho_basis();
	set_camera(cam);

	// Point Light
	PointLight *light_ptr2 = new PointLight;
	light_ptr2->set_color(0.8, 0.8, 0.8);
	light_ptr2->set_point(150.0, 520.0, 320.0);
	light_ptr2->scale_radiance(2.0);
	add_light(light_ptr2);

	background_color = background;
	tracer_ptr = new RayCast(this);

	// Floor
	Plane* plane_ptr = new Plane;
	plane_ptr->set_point(0.0, -10.0, -24.0);
	plane_ptr->set_normal(0.0, 1.0, 0.0);
	plane_ptr->set_dim(320, 20, 480);
	Phong *floor_matteptr = new Phong;
	floor_matteptr->set_ka(0.40);
	floor_matteptr->set_kd(0.60);
	floor_matteptr->set_cd(0.4, 0.3, 0.2);
	floor_matteptr->set_ks(0.6);
	floor_matteptr->set_cs(1, 1, 1);
	floor_matteptr->set_ex(20);
	plane_ptr->set_material(floor_matteptr);
	add_object(plane_ptr);
	
	// Blue Sphere
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(40, 55, -60);
	sphere_ptr->set_radius(30.0);
	Phong *matte_ptr2 = new Phong;
	matte_ptr2->set_ka(0.25);
	matte_ptr2->set_kd(0.65);
	matte_ptr2->set_cd(0.0, 0.2, 1.0);
	matte_ptr2->set_ks(0.4);
	matte_ptr2->set_cs(1, 1, 1);
	matte_ptr2->set_ex(2);
	sphere_ptr->set_material(matte_ptr2);
	add_object(sphere_ptr);

	// Orange Sphere
	sphere_ptr = new Sphere;
	sphere_ptr->set_center(80, 75, -35);
	sphere_ptr->set_radius(35.0);
	Phong *matte_ptr3 = new Phong;
	matte_ptr3->set_ka(0.25);
	matte_ptr3->set_kd(0.65);
	matte_ptr3->set_cd(1, 0.6, 0.2);
	sphere_ptr->set_material(matte_ptr3);
	add_object(sphere_ptr);


}

ShadeRec World::hit_objects(const Ray &ray)  {
	ShadeRec	sr(*this);
	double		t;
	Normal		normal;
	Point3D		local_hit_point;
	double		tmin = kHugeValue;
	int			num_objects = objects.size();

	for (int j = 0; j < num_objects; j++) {
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object = true;
			tmin = t;
			sr.material_ptr = objects[j]->get_material();
			sr.hit_point = ray.o + t * ray.d;
			normal = sr.normal;
			//sr.color = objects[j]->get_color();
		}
		if (sr.hit_an_object) {
			sr.t = tmin;
			sr.normal = normal;
			sr.local_hit_point = local_hit_point;
		}
	}
	return sr;
}