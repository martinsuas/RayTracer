#include "Pinhole.h"
#include "../World/ViewPlane.h"
#include "../Utilities/Vector3D.h"
#include <math.h>
#include "../Utilities/Constants.h"
#include <GL/freeglut.h>
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
				glColor3d(pixel_color.r, pixel_color.g, pixel_color.b);
				glBegin(GL_POLYGON);
				glVertex2d(c, r);
				double off = 1.0;
				glVertex2d(c + off, r);
				glVertex2d(c + off, r + off);
				glVertex2d(c, r + off);
				glEnd();
			}
		}
		glFlush();
	/*
	//RGBColor	L; 
	ViewPlane	vp(w.vp);
	Ray			ray;
	int 		depth = 0;
	RGBColor	pixel_color;
	double		zw = 100;
	double		x, y;
	//Point2D 	sp;		// sample point in [0,1] x [0,1]
	Point2D 	pp;		// sample point on a pixel

	//ray.d = Vector3D(0, 0, -1);

	vp.s /= zoom;
	//ray.o = eye;

	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	for (int r = 0; r < vp.vres; r++) {
		for (int c = 0; c < vp.hres; c++) {
			x = vp.s * (c - 0.5 * (vp.hres - 1.0));
			y = vp.s * (r - 0.5 * (vp.vres - 1.0));
			//ray.o = Point3D(x, y, zw);
			//ray.d = ray_direction(pp);
			ray.d = Vector3D(0, 0, -1);
			pixel_color = w.tracer_ptr->trace_ray(ray);
			// Equivalent of draw pixel
			//if (pixel_color.r == 1.0)
			//std::cout << x << ":" << y << std::endl;
			glColor3d(pixel_color.r, pixel_color.g, pixel_color.b);
			glBegin(GL_POLYGON);
			glVertex2d(c, r);
			double off = 1;
			glVertex2d(c + off, r);
			glVertex2d(c + off, r + off);
			glVertex2d(c, r + off);
			glEnd();
		}
	}
	glFlush();
	*/
	/*
	RGBColor	L;
	ViewPlane	vp(w.vp);
	Ray			ray;
	int 		depth = 0;
	Point2D 	pp;		// sample point on a pixel
	int n = (int)sqrt((float)vp.num_samples);

	vp.s /= zoom;
	ray.o = eye;

	for (int r = 0; r < vp.vres; r++)			// up
		for (int c = 0; c < vp.hres; c++) {		// across 					
			L = black;

			for (int p = 0; p < n; p++)			// up pixel
				for (int q = 0; q < n; q++) {	// across pixel
					pp.x = vp.s * (c - 0.5 * vp.hres + (q + 0.5) / n);
					pp.y = vp.s * (r - 0.5 * vp.vres + (p + 0.5) / n);
					ray.d = ray_direction(pp);
					L += w.tracer_ptr->trace_ray(ray, depth);
				}

			L *= exposure_time;
			w.display_pixel(r, c, L);
		}
*/

	/*
void World::render_scene(void) const{
	RGBColor	pixel_color;
	Ray			ray;
	double		zw = 100;
	double		x, y;

	//open_window(vp.hres, vp.vres);
	ray.d = Vector3D(0, 0, -1);

	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
	
	for (int r = 0; r < vp.vres; r++) {
		for (int c = 0; c < vp.hres; c++) {
			x = vp.s * (c - 0.5 * (vp.hres - 1.0));
			y = vp.s * (r - 0.5 * (vp.vres - 1.0));
			ray.o = Point3D(x, y, zw);
			pixel_color = tracer_ptr->trace_ray(ray);
			//if (pixel_color.r == 1.0)
				//std::cout << x << ":" << y << std::endl;
			glColor3d(pixel_color.r, pixel_color.g, pixel_color.b);
			glBegin(GL_POLYGON);
			glVertex2d(c, r);
			double off = 1.0;
			glVertex2d(c+off, r);
			glVertex2d(c + off, r + off);
			glVertex2d(c, r + off);
			glEnd();
		}
	}
	glFlush();
}
*/
}
