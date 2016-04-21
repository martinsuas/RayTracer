/*
Main program. Initialized glut and performs tracing calculations.
*/
#include "World.h"
#include <GL/freeglut.h>
int main(int argc, char** argv)
{
	World		w;
	glutInit(&argc, argv); // Initialize GLUT.
	w.build_tracer();
	w.camera_ptr->render_scene(w);
	glutMainLoop();
	//w.render_scene();
}