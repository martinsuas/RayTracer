/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
/*
Header used to perform simple math operations
*/
inline double max(double x0, double x1);
inline double min(double x0, double x1);

// Implementations:
inline double max(double x0, double x1) {
	return((x0 > x1) ? x0 : x1);
}

inline double min(double x0, double x1) {
	return((x0 < x1) ? x0 : x1);
}