#include "World.h"
#include "../Utilities/Constants.h"

// Geometric Objects
#include "../Geometric_Objects/Sphere.h"
#include "../Geometric_Objects/Triangle.h"

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
#include "../Materials/Transparent.h"

#include "../Textures/Checker3D.h"
#include "../Textures/ConstantColor.h"

#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/ShadeRec.h"

// Build Functions
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <ctime>


bool World::bufferFile(std::string objfile) {
	std::ifstream file;
	file.open(objfile);
	std::string line;
	int num_elements;
	int locN = 0, texN = 0, norN = 0, facN = 0;
	int locT = 0, texT = 0, norT = 0, facT = 0;
	std::vector<GLfloat> locs;
	std::vector<GLfloat> texs;
	std::vector<GLfloat> nors;
	std::vector<GLfloat> v;

	bool pLoc = false, pTex = false, pNor = false;

	while (getline(file, line)) {
		num_elements = 0;
		std::istringstream iss(line);
		std::string command;
		iss >> command;
		if (command.compare("v") == 0) {
			locT++;
			while (iss >> command) {
				num_elements++;
				locs.push_back(std::stof(command));
			}
			if (locN == 0)
				locN = num_elements;
		}
		else if (command.compare("vt") == 0) {
			// Debug
			if (pLoc) {
				for (int i = 0; i < locT*locN; i++) {
					if (i % locN == 0)
						std::cout << std::endl;
					std::cout << locs[i] << " ";
				}
				std::cout << std::endl << "locT: " << locT << std::endl;
				pLoc = false;
			}
			// end debug
			texT++;
			while (iss >> command) {
				num_elements++;
				texs.push_back(std::stof(command));
			}
			if (texN == 0)
				texN = num_elements;
		}
		else if (command.compare("vn") == 0) {
			// Debug
			if (pTex) {
				for (int i = 0; i < texT*texN; i++) {
					if (i % texN == 0)
						std::cout << std::endl;
					std::cout << texs[i] << " ";
				}
				std::cout << std::endl << "texT: " << texT << std::endl;
				pTex = false;
			}
			// end debug
			norT++;
			while (iss >> command) {
				num_elements++;
				nors.push_back(std::stof(command));
			}
			if (norN == 0)
				norN = num_elements;
		}
		else if (command.compare("f") == 0) {
			// Debug
			if (pNor) {
				for (int i = 0; i < norT*norN; i++) {
					if (i % norN == 0)
						std::cout << std::endl;
					std::cout << nors[i] << " ";
				}
				std::cout << std::endl << "norT: " << norT << std::endl;
				pNor = false;
			}
			// end debug
			while (iss >> command) {
				std::vector<int> elems;
				std::stringstream ss(command);
				std::string item;
				bool no_tex = false;
				int i = 0;
				while (std::getline(ss, item, '/')) {
					if (!item.empty())
						elems.push_back(std::stoi(item));
					else
						elems.push_back(0);
					i++;
				}

				//std::cout << elems.at(0) << " " << elems.at(1) << " " << elems.at(2)  << std::endl;

				if (i >= 1) {
					for (int j = 0; j < locN; j++) {
						v.push_back(locs.at((elems.at(0) - 1) * locN + j));
					}
					if (facN == 0)
						facN = i;
				}
				if (i >= 2) {
					if (elems.at(1) != 0) {
						for (int j = 0; j < texN; j++) {
							v.push_back(texs.at((elems.at(1) - 1) * texN + j));
							//std::cout << "tex" << std::endl;
						}
					}
					else {
						//std::cout << "NOOOOOOOOOOOOO" << std::endl;
					}
				}
				if (i >= 3) {
					if (elems.at(1) != 0) {
						for (int j = 0; j < norN; j++) {
							//std::cout << "  elemN: " << elems.at(2) << std::endl;
							v.push_back(nors.at((elems.at(2) - 1) * norN + j));
							//std::cout << "nor" << std::endl;
						}
					}
					else {
						for (int j = 0; j < norN; j++) {
							//std::cout << "  elemN: " << elems.at(2) << std::endl;
							v.push_back(nors.at((elems.at(2) - 1) * norN + j));
							//std::cout << "nor" << std::endl;
						}
					}
					
				}
			}
			facT++;
		}
	}
	/*
	std::cout << "facT: " << facT << std::endl;
	std::cout << "locN: " << locN << std::endl;
	std::cout << "texN: " << texN << std::endl;
	std::cout << "norN: " << norN << std::endl;
	*/
	unsigned int na = locN + texN + norN; // number of attributes

	int vertCount = facT * facN;

	int counter = 1;
	Point3D ta;
	Point3D tb;
	Point3D tc;
	/*
	for (int i = 0; i < na * 12 * 3; i += na) {
		for (int j = 0; j < na; j++) {
			std::cout << v[i + j] << " ";
		}
		std::cout << std::endl;
	}
	*/
	for (int i = 0; i < na * facT * 3; i += na) {
		if (counter == 1)
			ta = Point3D(v[i], v[i + 1], v[i + 2]);
		if (counter == 2)
			tb = Point3D(v[i], v[i + 1], v[i + 2]);
		if (counter == 3)
			tc = Point3D(v[i], v[i + 1], v[i + 2]);
		counter++;
		if (counter == 4) {
			Triangle* triangle = new Triangle(ta, tb, tc);
			ConstantColor* ccp = new ConstantColor;
			ccp->set_color(red);
			SV_Matte *matte_ptr4 = new SV_Matte;
			matte_ptr4->set_ka(0.25);
			matte_ptr4->set_kd(0.65);
			//matte_ptr4->set_cd(0.7);
			matte_ptr4->set_cd(ccp);
			
			
			triangle->set_material(matte_ptr4);
			add_object(triangle);
			counter = 1;
		}
	}
	return true;
}

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
	glutCreateWindow("Martin Suarez - Advanced Checkpoint 1"); // Create display window.
	glClearColor(background.r, background.g, background.b, 0.0); // Set display-window color to white.
	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	//gluOrtho2D(-width /2.0, width/2.0, -height /2.0, height /2.0);
	gluOrtho2D(0.0, width, 0.0, height);

	// RayTracer Parameters
	vp.set_hres(width);
	vp.set_vres(height);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	vp.set_max_depth(6);

	Ambient *ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(40.0);
	set_ambient_light(ambient_ptr);

	// Camera Parameters
	Pinhole* cam = new Pinhole();
	cam->set_eye(2, 2, -4);
	cam->set_eye(-10, 10, 10);
	//cam->set_eye(-4, 0, 0);
	cam->set_lookat(0, 0, 0);
	//cam->set_eye(70, 65, 200);
	//cam->set_lookat(70, 65, -500.0);
	cam->set_up(0.0, 1.0, 0.0); // try -1?
	cam->compute_ortho_basis();
	cam->set_max_lum(100);
	cam->set_max_d_lum(500);
	set_camera(cam);
	
	// Point Light
	PointLight *light_ptr2 = new PointLight;
	light_ptr2->set_color(0.8, 0.8, 0.8);
	light_ptr2->set_point(150.0, 520.0, 320.0);
	light_ptr2->scale_radiance(80.0);
	add_light(light_ptr2);

	background_color = background;
	tracer_ptr = new Whitted(this);

	// Floor
	//Cube* plane_ptr = new Cube;
	Rect* plane_ptr = new Rect(
		Point3D(-120, -10.0, 150), Vector3D(280, 0, 0), Vector3D(0, 0, -860));
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
	//add_object(plane_ptr);
	clock_t begin = clock();
	bufferFile("Objects/bunny1.obj");
	clock_t end = clock();
	double time = double(end - begin) / CLOCKS_PER_SEC;

	std::cout << "Time to build tree: " << time << std::endl;
	kdtree = new KD_Node();
	kdtree = kdtree->make(objects, 0);

	// Cube5
	/*
	Triangle* triangle = new Triangle(
		Point3D(40, 55, -60), Point3D(100, 0, 0), Point3D(20, 20, -20));
	ConstantColor* ccp = new ConstantColor;
	//ccp->set_size(32);
	//cp->set_color1(yellow);
	ccp->set_color(red);
	SV_Matte *matte_ptr4 = new SV_Matte;
	matte_ptr4->set_ka(0.25);
	matte_ptr4->set_kd(0.65);
	matte_ptr4->set_cd(ccp);
	triangle->set_material(matte_ptr4);
	add_object(triangle);

	
	// Green Cube
	
	Rect* cube_ptr = new Rect(
		Point3D(40, 55, -60), Vector3D(100, 0, 0), Vector3D(20, 20, -20));
	//cube_ptr->set_center(40, 55, -60);
	//cube_ptr->set_dim(50.0, 50.0, 50.0);

	//ConstantColor* ccp = new ConstantColor(green);
	ConstantColor* ccp = new ConstantColor;
	//ccp->set_size(32);
	//cp->set_color1(yellow);
	ccp->set_color(red);


	SV_Matte *matte_ptr4 = new SV_Matte;
	matte_ptr4->set_ka(0.25);
	matte_ptr4->set_kd(0.65);
	matte_ptr4->set_cd(ccp);
	//matte_ptr4->set_ks(0.4);
	//matte_ptr4->set_cs(1, 1, 1);
	//matte_ptr4->set_ex(2);
	cube_ptr->set_material(matte_ptr4);//matte_ptr4);
	add_object(cube_ptr);
	*/
	
	/*

	// Transparent Sphere
	Transparent *glass_ptr = new Transparent;
	glass_ptr->set_ka(0.075);
	glass_ptr->set_kd(0.075);
	glass_ptr->set_ks(0.2);
	glass_ptr->set_ex(20);
	glass_ptr->set_ior(0.95);
	glass_ptr->set_kr(0.01);
	glass_ptr->set_kt(0.8);
	glass_ptr->set_cs(white);
	glass_ptr->set_cd(white);
	Sphere* sphere_ptr2 = new Sphere;
	sphere_ptr2->set_center(80, 75, -35);
	sphere_ptr2->set_radius(35.0);
	sphere_ptr2->set_material(glass_ptr);
	//sphere_ptr->set_color(0, 0, 1);
	add_object(sphere_ptr2);

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
	matte_ptr2->set_kr(1.0);
	matte_ptr2->set_cs(1, 1, 1);
	matte_ptr2->set_cr(white);
	sphere_ptr->set_material(matte_ptr2);
	//sphere_ptr->set_color(0, 1, 0);
	add_object(sphere_ptr);
	*/

}

ShadeRec World::hit_objects(const Ray &ray)  {
	ShadeRec	sr(*this);
	double		t;
	Normal		normal;
	Point3D		local_hit_point;
	double		tmin = kHugeValue;
	int			num_objects = objects.size();

	hit(kdtree, ray, t, tmin, sr);	
	/*
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
	}
	if (sr.hit_an_object) {
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}
	*/
	return sr;
}

bool World::hit(KD_Node* node, const Ray &ray, double &t, double &tmin, ShadeRec &sr) const {
	if (node->bbox.hit(ray)) {
		Normal n;
		bool hit_obj = false;
		Point3D hit_p, local_hit_p;


		if (node->left->objs.size() > 0 || node->right->objs.size() > 0) {
			bool hitleft = hit(node->left, ray, t, tmin, sr);
			bool hitright = hit(node->right, ray, t, tmin, sr);
			return hitleft || hitright;
		}
		else { // leaf
			for (int i = 0; i < node->objs.size(); i++) {
				if (node->objs[i]->hit(ray, t, sr)) {
					hit_obj = true;
					sr.hit_an_object = true;
					tmin = t;
					sr.material_ptr = node->objs[i]->get_material();
					hit_p = ray.o + t * ray.d;
					n = sr.normal;
					sr.color = node->objs[i]->get_color();
					local_hit_p = sr.local_hit_point;

					//hit_p = sr.hit_point;
					//sr.local_hit_point
				}
			}
			if (hit_obj) {
				sr.hit_an_object = true;
				sr.t = tmin;
				sr.normal = n;
				sr.local_hit_point = local_hit_p;
				sr.hit_point = hit_p;
				return true;
			}
			return false;
		}
	}
	return false;
}