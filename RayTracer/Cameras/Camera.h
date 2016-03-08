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

	// Functions
	void compute_ortho_basis();
	// Each cameras renders the scene.
	virtual void render_scene(const World &w) = 0;

protected:
	Point3D eye, lookat;
	Vector3D up;
	// View defined using orthonormal basis (u,v,w)
	Vector3D u, v, w;
	// Chapter 28
	float exposure_time;

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