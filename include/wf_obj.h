#ifndef WF_OBJ_H
#define WF_OBJ_H

#include <Eigen/Eigen>
#include <memory>
#include <string>

struct vertex {
	Eigen::Vector4f pos;
};

struct triangle {
	size_t v1;
    size_t v2;
	size_t v3;
};

struct Object {
	std::shared_ptr<std::vector<triangle>> triangles;
	std::shared_ptr<std::vector<vertex>> verteces;
	
	Object(std::shared_ptr<std::vector<triangle>> triangles, std::shared_ptr<std::vector<vertex>> verteces);

	void translate(Eigen::Vector3f translation);

};

std::shared_ptr<Object> load_obj(const std::string &path);

#endif
