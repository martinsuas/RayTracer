#include "World.h"
#include "../Utilities/Constants.h"

// Geometric Objects
#include "../Geometric_Objects/Plane.h"
#include "../Geometric_Objects/Sphere.h"
#include "../Geometric_Objects/Cube.h"

#include "../Tracers/SingleSphere.h"
#include "../Tracers/MultipleObjects.h"
#include "../Tracers/RayCast.h"
#include "../Tracers/Whitted.h"

#include "../Cameras/Pinhole.h"

#include "../Lights/Directional.h"
#include "../Lights/PointLight.h"

#include "../Materials/Matte.h"
#include "../Materials/Phong.h"
#include "../Materials/SV_Matte.h"
#include "../Materials/Reflective.h"

#include "../Textures/Checker3D.h"

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

void World::build_tracer(void) {
	RGBColor background = RGBColor(0, 0.4, 0.6);

	// OpenGL Paramaters
	// Using single buffer, RGB color select
	float width = 400;
	float height = 400;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode.
	glutInitWindowPosition(50, 100); // Set top-left display-window position.
	glutInitWindowSize(width, height); // Set display-window width and height.
	glutCreateWindow("Martin Suarez - Checkpoint 5"); // Create display window.
	glClearColor(background.r, background.g, background.b, 0.0); // Set display-window color to white.
	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	//gluOrtho2D(-width /2.0, width/2.0, -height /2.0, height /2.0);
	gluOrtho2D(0.0, width, 0.0, height);

	// RayTracer Parameters
	vp.set_hres(width);
	vp.set_vres(height);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	vp.set_max_depth(10);

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
	tracer_ptr = new Whitted(this);

	// Floor
	//Cube* plane_ptr = new Cube;
	Cube* plane_ptr = new Cube(Point3D(-120, -10.0, 150), Vector3D(280, 0, 0), Vector3D(0, 0, -860));
	//plane_ptr->set_point(0.0, -10.0, -24.0);
	//plane_ptr->set_normal(0.0, 1.0, 0.0);
	//plane_ptr->set_dim(320, 20, 480);

	Checker3D* checker_ptr1 = new Checker3D;
	checker_ptr1->set_size(32);
	checker_ptr1->set_color1(yellow);
	checker_ptr1->set_color2(red);

	//plane_ptr->set_dim(3200, 20, 4800);
	SV_Matte *floor_matteptr = new SV_Matte;
	floor_matteptr->set_ka(0.40);
	floor_matteptr->set_kd(0.60);
	floor_matteptr->set_cd(checker_ptr1);

	plane_ptr->set_material(floor_matteptr);
	//plane_ptr->set_color(1, 0, 0);
	add_object(plane_ptr);

	/*
	// Green Cube
	Cube* cube_ptr = new Cube(Point3D(40, 55, -60), Vector3D(100, 0, 0) , Vector3D(0,0, 100) );
	//cube_ptr-> set_center(40, 55, -60);
	//cube_ptr->set_dim(50.0, 50.0, 50.0);
	Phong *matte_ptr4 = new Phong;
	matte_ptr4->set_ka(0.25);
	matte_ptr4->set_kd(0.65);
	matte_ptr4->set_cd(0.6, 0.6, 0.4);
	matte_ptr4->set_ks(0.4);
	matte_ptr4->set_cs(1, 1, 1);
	matte_ptr4->set_ex(2);
	cube_ptr->set_material(floor_matteptr);//matte_ptr4);
	add_object(cube_ptr);
	*/

	// Reflective Sphere
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(25, 55, -90);
	sphere_ptr->set_radius(30.0);

	Reflective *matte_ptr2 = new Reflective;
	matte_ptr2->set_ka(0.25);
	matte_ptr2->set_kd(0.65);
	matte_ptr2->set_cd(0.2, 0.2, 0.2);
	matte_ptr2->set_ks(0.25);
	matte_ptr2->set_ex(5);
	matte_ptr2->set_kr(0.99);
	matte_ptr2->set_cs(1, 1, 1);
	matte_ptr2->set_cr(white);
	sphere_ptr->set_material(matte_ptr2);
	//sphere_ptr->set_color(0, 1, 0);
	add_object(sphere_ptr);

	// Black Sphere
	sphere_ptr = new Sphere;
	sphere_ptr->set_center(80, 75, -35);
	sphere_ptr->set_radius(35.0);
	Phong *matte_ptr3 = new Phong;
	matte_ptr3->set_ka(0.25);
	matte_ptr3->set_kd(0.65);
	matte_ptr3->set_cd(0.1, 0.1, 0.1);
	sphere_ptr->set_material(matte_ptr3);
	//sphere_ptr->set_color(0, 0, 1);
	add_object(sphere_ptr);
}

void World::build_project(void) {
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
	vp.set_max_depth(10);

	Ambient *ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr);

	// Camera Parameters
	Pinhole* cam = new Pinhole();
	cam->set_eye(-360, 40, -360);
	cam->set_lookat(180, 40, 120);
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
	plane_ptr->set_point(100.0, 0.0, 100.0);
	plane_ptr->set_normal(0.0, 1.0, 0.0);
	plane_ptr->set_dim(2000, 1, 2000);
	Matte *floor_matteptr = new Matte;
	floor_matteptr->set_ka(0.40);
	floor_matteptr->set_kd(0.60);
	floor_matteptr->set_cd(0.22, 0.5, 0.2);
	//floor_matteptr->set_ks(0.6);
	//floor_matteptr->set_cs(1, 1, 1);
	//floor_matteptr->set_ex(20);
	plane_ptr->set_material(floor_matteptr);
	//plane_ptr->set_color(1, 0, 0);
	add_object(plane_ptr);

	// Cloth
	plane_ptr->set_point(100.0, 20.0, 100.0);
	plane_ptr->set_normal(0.0, 0.0, 1.0);
	plane_ptr->set_dim(20, 40, 20);
	floor_matteptr = new Matte;
	floor_matteptr->set_ka(0.40);
	floor_matteptr->set_kd(0.60);
	floor_matteptr->set_cd(0.6, 0.4, 0.4);
	//floor_matteptr->set_ks(0.6);
	//floor_matteptr->set_cs(1, 1, 1);
	//floor_matteptr->set_ex(20);
	plane_ptr->set_material(floor_matteptr);
	//plane_ptr->set_color(1, 0, 0);
	add_object(plane_ptr);


	// Pole 1
	Cube* pole1_ptr = new Cube;
	//pole1_ptr->set_center(180.0, 100.0, 40.0);
	//pole1_ptr->set_center(180.0, 20, 40.0);
	//pole1_ptr->set_normal(0.0, 1.0, 0.0);
	//pole1_ptr->set_dim(2, 160, 2);
	Phong *pole1_phongptr = new Phong;
	pole1_phongptr->set_ka(0.40);
	pole1_phongptr->set_kd(0.60);
	pole1_phongptr->set_cd(0.4, 0.37, 0.17);
	pole1_phongptr->set_ks(0.6);
	pole1_phongptr->set_cs(1, 1, 1);
	pole1_phongptr->set_ex(20);
	pole1_ptr->set_material(pole1_phongptr);
	add_object(pole1_ptr);

	// Transparent Sphere
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(180, 20, 40);
	sphere_ptr->set_radius(10);
	Phong *matte_ptr2 = new Phong;
	matte_ptr2->set_ka(0.25);
	matte_ptr2->set_kd(0.65);
	matte_ptr2->set_cd(0.0, 0.2, 1.0);
	matte_ptr2->set_ks(0.4);
	matte_ptr2->set_cs(1, 1, 1);
	matte_ptr2->set_ex(2);
	sphere_ptr->set_material(matte_ptr2);
	//sphere_ptr->set_color(0, 1, 0);
	add_object(sphere_ptr);

	// Orange Sphere
	sphere_ptr = new Sphere;
	sphere_ptr->set_center(180, 20, 200);
	sphere_ptr->set_radius(10.0);
	Phong *matte_ptr3 = new Phong;
	matte_ptr3->set_ka(0.25);
	matte_ptr3->set_kd(0.65);
	matte_ptr3->set_cd(1, 0.6, 0.2);
	sphere_ptr->set_material(matte_ptr3);
	//sphere_ptr->set_color(0, 0, 1);
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
			sr.color = objects[j]->get_color();
			local_hit_point = sr.local_hit_point;
		}
		if (sr.hit_an_object) {
			sr.t = tmin;
			sr.normal = normal;
			sr.local_hit_point = local_hit_point;
		}
	}
	return sr;
}