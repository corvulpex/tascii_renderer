#ifndef OBJECT_H
#define OBJECT_H

#include "wf_obj.h"
#include <Eigen/src/Core/Matrix.h>
#include <memory>

class Object {
	
	std::shared_ptr<std::vector<triangle>> triangles;
	
public:
	Object(std::shared_ptr<std::vector<triangle>> triangles);

	void translate(Eigen::Vector3f translation);

};

#endif
