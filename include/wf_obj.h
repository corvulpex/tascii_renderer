#ifndef WF_OBJ_H
#define WF_OBJ_H

#include <Eigen/Eigen>
#include <memory>
#include <string>
#include <vector>

struct vertex {
	Eigen::Vector4f pos;
};

struct triangle {
    vertex v1;
    vertex v2;
    vertex v3;
};

std::shared_ptr<std::vector<triangle>> load_obj(const std::string &path);

#endif
