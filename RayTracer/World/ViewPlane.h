#pragma once

class ViewPlane {
public:
	int		hres;		// Horizontal image res
	int		vres;		// Vertical image res
	int		num_samples;// Number of samples per pixel
	int		max_depth;
	float	s;			// Pixel size
	float	gamma;		// Monitor gamma factor
	float	inv_gamma;	// 1/gamma

	ViewPlane();

	ViewPlane(const ViewPlane &vp);

	ViewPlane& operator= (const ViewPlane &rhs);

	~ViewPlane();

	void set_hres(const int h_res);

	void set_vres(const int v_res);

	void set_pixel_size(const float size);

	void set_gamma(const float g);

	void set_samples(const int num_samples);

	void set_max_depth(const int d);
};

inline void
ViewPlane::set_hres(const int h_res) {
	hres = h_res;
}

inline void
ViewPlane::set_vres(const int v_res) {
	vres = v_res;
}

inline void
ViewPlane::set_pixel_size(const float size) {
	s = size;
}

inline void
ViewPlane::set_gamma(const float g) {
	gamma = g;
	inv_gamma = 1.0f / gamma;
}

inline void
ViewPlane::set_samples(const int s) {
	num_samples = s;
}

inline void
ViewPlane::set_max_depth(const int d) {
	max_depth = d;
}