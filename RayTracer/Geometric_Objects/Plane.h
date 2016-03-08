#pragma once
#include "GeometricObject.h"

class Plane : public GeometricObject {
public:
	virtual bool hit(const Ray &ray, double &t, ShadeRec &s) const;
	virtual bool shadow_hit(const Ray &ray, double &t) const;
	// Constructors
	Plane(void);
	Plane(const Point3D& point, const Normal& normal);
	Plane(const Point3D& point, const Point3D& dim, const Normal& normal);
	Plane(const Plane& plane); 
	virtual	~Plane(void);

	// Setters
	void set_point(const Point3D &p);
	void set_point(const float x, const float y, const float z);
	void set_dim(const Point3D &p);
	void set_dim(const float x, const float y, const float z);
	void set_normal(const Normal &n);
	void set_normal(const float x, const float y, const float z);

	// Operator
	Plane& operator= (const Plane& rhs);

	// Operations
	virtual Plane* clone(void) const;

private:
	Point3D				a;		// Point where plane passes
	Point3D				dim;		// Point where plane passes
	Normal				n;		// Normal to the plane

	static const double	kEpsilon;	// --FUTURE--
};
// Inline functions

inline void Plane::set_point(const Point3D &p) { a = p; }
inline void Plane::set_point(const float x, const float y, const float z) {
	a.x = x;
	a.y = y;
	a.z = z;
}
inline void Plane::set_dim(const Point3D &p) { dim = p; }
inline void Plane::set_dim(const float x, const float y, const float z) {
	dim.x = x;
	dim.y = y;
	dim.z = z;
}
inline void Plane::set_normal(const Normal &no) { n = no; }
inline void Plane::set_normal(const float x, const float y, const float z) {
	n.x = x;
	n.y = y;
	n.z = z;
}
