/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include "Pinhole.h"
#include "../World/ViewPlane.h"
#include "../Utilities/Vector3D.h"
#include <math.h>
#include "../Utilities/Constants.h"
#include <GL/freeglut.h>
#include <iostream>
// Constructors
Pinhole::Pinhole(void) :
	Camera(),
	d(500),
	zoom(1.0)
{}
Pinhole::Pinhole(const Pinhole& c) : 
	Camera(c),
	d(c.d),
	zoom(c.zoom)
{}
Pinhole::~Pinhole() {}

// Operators
Pinhole& Pinhole::operator= (const Pinhole &o) {
	if (this == &o)
		return *this;
	Camera::operator= (o);
	d = o.d;
	zoom = o.zoom;
	return *this;
}

// Functions
Vector3D Pinhole::ray_direction(const Point2D& p) const {
	Vector3D dir = p.x * u + p.y * v - d * w;
	dir.normalize();
	return dir;
}

void Pinhole::render_scene(const World &w) {
	RGBColor	pixel_color;
	Ray			ray;
	//double		zw = 100;
	//double		x, y;
	int			n = (int)sqrt((float)w.vp.num_samples);
	Point2D		pp;  // Sample point on a pixel
	//ray.d = Vector3D(0, 0, -1);
	ray.o = eye;

	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
	/*
	// Find average luminance of the scene
	float aL = 0;

	for (int r = 0; r < w.vp.vres; r++) {
		for (int c = 0; c < w.vp.hres; c++) {
			for (int p = 0; p < n; p++) {
				for (int q = 0; q < n; q++) {
					// Aliasing 
					pp.x = w.vp.s * (c - 0.5 * w.vp.hres + (q + 0.5) / n);
					pp.y = w.vp.s * (r - 0.5 * w.vp.vres + (p + 0.5) / n);
					//ray.o = Point3D(pp.x, pp.y, zw);
					ray.d = ray_direction(pp);
					// Sum colors
					pixel_color += w.tracer_ptr->trace_ray(ray);
				}
			}
			pixel_color /= w.vp.num_samples;
			aL += std::log(0.000000001 + (0.27 * pixel_color.r + 0.67 * pixel_color.g + 0.06 * pixel_color.b));
		}
	}
	aL = std::exp(aL / (w.vp.vres * w.vp.hres));
	std::cout << aL << std::endl;

	*/
	bool print_once = false;
	for (int r = 0; r < w.vp.vres; r++) {
		for (int c = 0; c < w.vp.hres; c++) {
			for (int p = 0; p < n; p++)
				for (int q = 0; q < n; q++) {
					// Aliasing 
					pp.x = w.vp.s * (c - 0.5 * w.vp.hres + (q + 0.5) / n);
					pp.y = w.vp.s * (r - 0.5 * w.vp.vres + (p + 0.5) / n);
					//ray.o = Point3D(pp.x, pp.y, zw);
					ray.d = ray_direction(pp);
					// Sum colors
					pixel_color += w.tracer_ptr->trace_ray(ray);
				}
			// Average
			pixel_color /= w.vp.num_samples;
			/*
			float R = pixel_color.r;
			float G = pixel_color.g;
			float B = pixel_color.b;
			//aL *= max_lum;


			if (print_once) {
				std::cout << "R " << R << std::endl;
				std::cout << "G " << G << std::endl;
				std::cout << "B " << B << std::endl;
				std::cout << "aL " << aL << std::endl;
			}


			float L = 0.27 * R + 0.67 * G + 0.06 * B;

			float sf;

			if (true) { // True for Ward, false for Rein
				float num = 1.219 + std::pow((max_lum / 2), 0.4);
				float dnum = 1.219 + std::pow(aL, 0.4);
				sf = std::pow(num / dnum, 2.5) / max_lum;

				if (print_once) {
					std::cout << "sf " << sf << std::endl;
				}

				L *= sf;
				R /= sf;
				//R = (L - 0.67 * G - 0.06 * B) / 0.27;
				G /= sf;
				//G = (L - 0.27 * R - 0.06 * B) / 0.67;
				B /= sf;
				//B = (L - 0.67 * G - 0.27 * R) / 0.06;
				if (print_once) {
					std::cout << "R " << R << std::endl;
					std::cout << "G " << G << std::endl;
					std::cout << "B " << B << std::endl;
				}

			}
			else {
				R = (0.18 * R) / aL;
				G = (0.18 * G) / aL;
				B = (0.18 * B) / aL;
				if (print_once) {
					std::cout << "R " << R << std::endl;
					std::cout << "G " << G << std::endl;
					std::cout << "B " << B << std::endl;
				}

				R = (R / (1 + R) * max_lum);
				G = (G / (1 + G) * max_lum);
				B = (B / (1 + B) * max_lum);
				if (print_once) {
					std::cout << "R " << R << std::endl;
					std::cout << "G " << G << std::endl;
					std::cout << "B " << B << std::endl;
				}
			}

			// Apply to device
			R /= max_d_lum;
			G /= max_d_lum;
			B /= max_d_lum;

			if (print_once) {
				std::cout << "R " << R << std::endl;
				std::cout << "G " << G << std::endl;
				std::cout << "B " << B << std::endl;
				print_once = false;
			}
			*/

			glColor3d(pixel_color.r, pixel_color.g, pixel_color.b);
			glBegin(GL_POLYGON);
			glVertex2d(c, r);
			double off = 1.0;
			glVertex2d(c + off, r);
			glVertex2d(c + off, r + off);
			glVertex2d(c, r + off);
			glEnd();
			pixel_color = 0;
		}
	}
	glFlush();
}
