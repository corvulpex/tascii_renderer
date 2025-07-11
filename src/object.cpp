#include "object.h"
#include <Eigen/src/Core/Matrix.h>
#include <memory>
#include <vector>


Object::Object(std::shared_ptr<std::vector<triangle>> triangles) {
	this->triangles = triangles;
	
}


void Object::translate(Eigen::Vector3f translation) {
	for (auto &t: *triangles) {
		t.v1.pos += Eigen::Vector4f{translation.x(), translation.y(), translation.z(), 0};
		t.v2.pos += Eigen::Vector4f{translation.x(), translation.y(), translation.z(), 0};
		t.v3.pos += Eigen::Vector4f{translation.x(), translation.y(), translation.z(), 0};
	
	}
}

