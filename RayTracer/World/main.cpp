/*
Main program. Initialized glut and performs tracing calculations.
*/
#include "World.h"
#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
int main(int argc, char** argv)
{
	clock_t begin = clock();
	World		w;
	glutInit(&argc, argv); // Initialize GLUT.
	w.build_tracer();
	w.camera_ptr->render_scene(w);
	clock_t end = clock();
	double time = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Time to render: " << time << std::endl;
	glutMainLoop();
	//w.render_scene();
}