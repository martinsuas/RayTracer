/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
#pragma once
/*
This header contains some constants for the Ray Tracer.
*/
#include <stdlib.h>
#include "../Utilities/RGBColor.h"

// Trig
const double 	PI = 3.1415926535897932384;
const double 	TWO_PI = 6.2831853071795864769;
const double 	PI_ON_180 = 0.0174532925199432957;
const double 	invPI = 0.3183098861837906715;
const double 	invTWO_PI = 0.1591549430918953358;

// Shading
const double 	kEpsilon = 0.0001;
const double	kHugeValue = 1.0E10;

const RGBColor black(0.0);
const RGBColor red(1.0, 0.0, 0.0);
const RGBColor yellow(1.0, 1.0, 0.0);
const RGBColor purple(1.0, 0.0, 1.0);
const RGBColor green(0.0, 1.0, 0.0);
const RGBColor blue(0.0, 0.0, 1.0);

const RGBColor white(1.0);

const float 	invRAND_MAX = 1.0f / (float)RAND_MAX;