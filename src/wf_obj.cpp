#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

#include "wf_obj.h"


std::shared_ptr<std::vector<triangle>> load_obj(const std::string &path) {
    std::ifstream file;
    file.open(path);
	if (!file.is_open()) {
		return nullptr;
	}


    size_t vertex_count = 0;
    size_t face_count = 0;

	std::string line;
    while (std::getline(file, line)) {
        if (line[0] == 'v') {
            vertex_count++;
        }
        else if(line[0] == 'f') {
            face_count++;
        }
    }

    vertex verteces[vertex_count];
    size_t vi = 0;
	auto triangles = std::make_shared<std::vector<triangle>>();

    file.clear();
    file.seekg(0, std::ios::beg);

    while(std::getline(file, line)) {
        if(line[0] == 'v') {
			sscanf(line.c_str(), "v %f %f %f", &verteces[vi].pos.x(), &verteces[vi].pos.y(), &verteces[vi].pos.z());
			verteces[vi].pos.w() = 1.0f;
			vi++;
        }
        else if (line[0] == 'f') {
			int vi[3];
			sscanf(line.c_str(), "f %d %d %d", vi, vi + 1, vi + 2);
			triangles->emplace_back(verteces[vi[0] - 1], verteces[vi[1] - 1], verteces[vi[2] - 1]);
        }
    }

	file.close();
	return triangles;
}
