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