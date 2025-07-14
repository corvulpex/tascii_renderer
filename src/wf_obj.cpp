#include <Eigen/Eigen>
#include <Eigen/src/Core/Matrix.h>
#include <fstream>
#include <memory>

#include "wf_obj.h"

Object::Object(std::shared_ptr<std::vector<triangle>> triangles, std::shared_ptr<std::vector<vertex>> verteces): triangles(triangles), verteces(verteces) {}


void Object::translate(Eigen::Vector3f translation) {
	Eigen::Vector4f trans = Eigen::Vector4f{translation.x(), translation.y(), translation.z(), 0};
	for (auto &v: *verteces) {
		v.pos += trans;
	}
}

std::shared_ptr<Object> load_obj(const std::string &path) {
    std::ifstream file;
    file.open(path);
	if (!file.is_open()) {
		return nullptr;
	}

	std::string line;
	auto verteces_pointer = std::make_shared<std::vector<vertex>>();
	auto triangles_pointer = std::make_shared<std::vector<triangle>>();

	// scanning verteces and triangles from file
    while(std::getline(file, line)) {
        if(line[0] == 'v') {
			float f[3];
			sscanf(line.c_str(), "v %f %f %f", f, f + 1, f + 2);
			verteces_pointer->emplace_back(Eigen::Vector4f{f[0], f[1], f[2], 1.0f}, Eigen::Vector4f{0, 255, 0, 255}, Eigen::Vector4f{0.0f, 0.0f, 0.0f, 0.0f});
        }
        else if (line[0] == 'f') {
			int vi[3];
			sscanf(line.c_str(), "f %d %d %d", vi, vi + 1, vi + 2);
			triangles_pointer->emplace_back(vi[0] - 1, vi[1] - 1, vi[2] - 1);
        }
    }

	file.close();

	std::vector<vertex> verteces = *verteces_pointer;
	// calculating normals
	for (auto &t: *triangles_pointer) {
		Eigen::Vector3f A = verteces[t.v3].pos.head<3>() - verteces[t.v1].pos.head<3>();
		Eigen::Vector3f B = verteces[t.v2].pos.head<3>() - verteces[t.v1].pos.head<3>();
		
		Eigen::Vector3f t_normal = A.cross(B);
		
		Eigen::Vector4f tn4{t_normal.x(), t_normal.y(), t_normal.z(), 0.0f};

		verteces[t.v1].normal += tn4;
		verteces[t.v2].normal += tn4;
		verteces[t.v3].normal += tn4;
	}
	for (auto &v: verteces) {
		v.normal.normalize();
	}


	auto object = std::make_shared<Object>(triangles_pointer, verteces_pointer);
	return object;
}


