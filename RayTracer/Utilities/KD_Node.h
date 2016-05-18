#pragma once
#include "../Geometric_Objects/Triangle.h"
#include "../Utilities/BBox.h"
#include <vector>
using std::vector;

class KD_Node {
public:
	KD_Node * left;
	KD_Node * right;
	BBox bbox;
	vector<GeometricObject*> objs;

	KD_Node();
	~KD_Node();

	KD_Node* make(vector<GeometricObject*> & objs, int depth) const;
};