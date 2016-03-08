#pragma once

class Point2D {
public:
	float x, y;
	// Constructors
	Point2D();
	Point2D(const float c);
	Point2D(const float x, const float y);
	Point2D(const Point2D &point);
	~Point2D(void);

	// Operators
	Point2D& operator= (const Point2D &p);
	Point2D operator* (const float f) const;
};
// Inline member functions
inline Point2D Point2D::operator*(const float f) const {
	return Point2D(f*x, f*y);
}