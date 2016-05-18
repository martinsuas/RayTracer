/*
Code ased on a frogslayer code, adapted to the RayTracer model of
BBox and GeometryObjects.
https://blog.frogslayer.com/kd-trees-for-faster-ray-tracing-with-triangles/
*/
#include "KD_Node.h"
#include <iostream>
KD_Node::KD_Node() {}
KD_Node::~KD_Node() {}

KD_Node* KD_Node::make(vector<GeometricObject *> &objects, int depth) const {
	//std::cout << "Depth: " << depth  << std::endl;
	KD_Node* node = new KD_Node();
	node->objs = objects;
	node->left = NULL;
	node->right = NULL;
	node->bbox = BBox();
	//std::cout << " On " << node->objs.size() << std::endl;

	if (objects.size() == 0)
		return node;

	if (objects.size() == 1) { // if a leaf
		node->bbox = objects.at(0)->get_bounding_box();
		node->left = new KD_Node();
		node->right = new KD_Node();
		node->left->objs = vector<GeometricObject *>();
		node->right->objs = vector<GeometricObject *>();
		return node;
	}

	// Get biggest bbox
	node->bbox = objects.at(0)->get_bounding_box();
	for (int i = 1; i < objects.size(); i++) {
		node->bbox.expand(objects.at(i)->get_bounding_box());
	}

	// Calc median point
	Point3D med = Point3D();
	for (int i = 0; i < objects.size(); i++) {
		med.x += objects[i]->get_point().x;
		med.y += objects[i]->get_point().y;
		med.z += objects[i]->get_point().z;
		
	}
	med.x = med.x / objects.size();
	med.y = med.y / objects.size();
	med.z = med.z / objects.size();

	//med = med * (1 / objects.size());


	// Split
	vector<GeometricObject *> left;
	vector<GeometricObject *> right;

	int axis_of_split = node->bbox.longest_axis();

	for (int i = 0; i < objects.size(); i++) {
		if (axis_of_split == 1) {
			if (objects[i]->get_point().x <= med.x)
				left.push_back(objects[i]);
			else
				right.push_back(objects[i]);
		}
		else if (axis_of_split == 2) {
			if (objects[i]->get_point().y <= med.y)
				left.push_back(objects[i]);
			else
				right.push_back(objects[i]);
		}
		else if (axis_of_split == 3) {
			if (objects[i]->get_point().z <= med.z)
				left.push_back(objects[i]);
			else
				right.push_back(objects[i]);
		}
		else {
			std::cout << "ERROR";
		}
	}

	if (left.size() == 0 && right.size() > 0)
		left = right;
	if (right.size() == 0 && left.size() > 0)
		right = left;

	int count = 0;
	for (int i = 0; i < left.size(); i++) {
		for (int j = 0; j < right.size(); j++) {
			if (left[i] == right[j])
				count++;
		}
	}

	// Only split if at least half dont match
	if ((float)count / left.size() < 0.5 && (float)count / right.size() < 0.5) {
		node->left = make(left, depth + 1);
		node->right = make(right, depth + 1);
	} 
	else {
		node->left = new KD_Node();
		node->right = new KD_Node();
		node->left->objs = vector<GeometricObject *>();
		node->right->objs = vector<GeometricObject *>();
	}

	return node;
}
