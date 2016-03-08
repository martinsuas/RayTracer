#pragma once
#include "GeometricObject.h"
class Cube : public GeometricObject {
public:
	// Constructors
	Cube(void);		// Default constructor

	Cube(const Point3D center, const Point3D dim); // Constructor

	Cube(const Cube &cub);

	virtual Cube* clone(void) const;

	virtual ~Cube(void);

	// Operators
	Cube& operator= (const Cube &cub);

	// Operations
	void set_center(const Point3D &c);

	void set_center(const double x, const double y, const double z);

	void set_dim(const Point3D &c);

	void set_dim(const double x, const double y, const double z);

	virtual bool hit(const Ray &ray, double &t, ShadeRec &sr) const;
	virtual bool shadow_hit(const Ray &ray, double &t) const;

private:
	Point3D					center;	  // Location of the center of the rect.
	Point3D					dim;	  // Specifies dimensions of Cube.
	static const double		kEpsilon; // --FUTURE--
};

// Inline functions
inline void Cube::set_center(const Point3D& c) {
	center = c;
}

inline void Cube::set_center(const double x, const double y, const double z) {
	center.x = x;
	center.y = y;
	center.z = z;
}
inline void Cube::set_dim(const Point3D& d) {
	dim = d;
}

inline void Cube::set_dim(const double x, const double y, const double z) {
	dim.x = x;
	dim.y = y;
	dim.z = z;
}