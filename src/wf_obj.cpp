#include <iostream>
#include <fstream>

#include "wf_obj.h"


std::vector<triangle> load_obj(const std::string &path) {
    std::ifstream file;
    file.open(path);
	if (!file.is_open()) {
		return std::vector<triangle>();
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
	std::vector<triangle> triangles;

    file.clear();
    file.seekg(0, std::ios::beg);

    while(std::getline(file, line)) {
        if(line[0] == 'v') {
			sscanf(line.c_str(), "v %f %f %f", &verteces[vi].x, &verteces[vi].y, &verteces[vi].z);
			vi++;
        }
        else if (line[0] == 'f') {
			int vi[3];
			sscanf(line.c_str(), "f %d %d %d", vi, vi + 1, vi + 2);
			triangles.emplace_back(verteces[vi[0] - 1], verteces[vi[1] - 1], verteces[vi[2] - 1]);
        }
    }

	file.close();
	return triangles;
}
