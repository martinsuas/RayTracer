/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#include "Camera.h"

// Constructors
Camera::Camera() :
	eye(0, 0, 300),
	lookat(0),
	up(0,1,0),
	u(1,0,0),
	v(0,1,0),
	w(0,0,1),
	exposure_time(1.0),
	max_lum(100),
	max_d_lum(500)
{};
Camera::Camera(const Camera &c) :
	eye(c.eye),
	lookat(c.lookat),
	up(c.up),
	u(c.u),
	v(c.v),
	w(c.w),
	exposure_time(c.exposure_time),
	max_lum(c.max_lum),
	max_d_lum(c.max_d_lum)
{}
Camera::~Camera() {}

// Operators
Camera& Camera::operator=(const Camera &cam) {
	if (this == &cam)
		return *this;
	eye = cam.eye;
	lookat = cam.lookat;
	up = cam.up;
	u = cam.u;
	v = cam.v;
	exposure_time = cam.exposure_time;
	max_lum = cam.max_lum;
	max_d_lum = cam.max_d_lum;
	return *this;
}

// Functions
void Camera::compute_ortho_basis() {
	w = eye - lookat;
	w.normalize();
	u = up ^ w;
	u.normalize();
	v = w ^ u;

	if (eye.x == lookat.x && eye.z == lookat.z && eye.y > lookat.y) { // camera looking vertically down
		u = Vector3D(0, 0, 1);
		v = Vector3D(1, 0, 0);
		w = Vector3D(0, 1, 0);
	}

	if (eye.x == lookat.x && eye.z == lookat.z && eye.y < lookat.y) { // camera looking vertically up
		u = Vector3D(1, 0, 0);
		v = Vector3D(0, 0, 1);
		w = Vector3D(0, -1, 0);
	}
}