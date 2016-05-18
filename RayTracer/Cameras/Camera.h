/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"

class World;

class Camera {
public:
	// Constructors
	Camera();
	Camera(const Camera &camera);
	~Camera();

	// Setters and getters
	void set_eye(const Point3D &p);
	void set_eye(const float x, const float y, const float z);
	void set_lookat(const Point3D &p);
	void set_lookat(const float x, const float y, const float z);
	void set_up(const Vector3D &v);
	void set_up(const float x, const float y, const float z);
	void set_max_lum(const float lum);
	void set_max_d_lum(const float lum);

	// Functions
	void compute_ortho_basis();
	// Each cameras renders the scene.
	virtual void render_scene(const World &w) = 0;

protected:
	Point3D eye, lookat;
	Vector3D up;
	Vector3D u, v, w;
	// Ch 28
	float exposure_time;
	float max_lum, max_d_lum;

	// Operators
	Camera& operator=(const Camera &cam);
};

// Inline Functions
inline void Camera::set_eye(const Point3D &p) { eye = p; }
inline void Camera::set_eye(const float x, const float y, const float z) {
	eye.x = x;
	eye.y = y;
	eye.z = z;
}
inline void Camera::set_lookat(const Point3D &p) { lookat = p; }
inline void Camera::set_lookat(const float x, const float y, const float z) {
	lookat.x = x;
	lookat.y = y;
	lookat.z = z;
}
inline void Camera::set_up(const Vector3D &v) { up = v; }
inline void Camera::set_up(const float x, const float y, const float z) {
	up.x = x;
	up.y = y;
	up.z = z;
}

inline void Camera::set_max_lum(const float lum) {
	max_lum = lum;
}

inline void Camera::set_max_d_lum(const float lum) {
	max_d_lum = lum;
}