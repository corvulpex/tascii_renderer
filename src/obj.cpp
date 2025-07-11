#include <iostream>
#include <fstream>

#include "obj.h"


struct triangle* load_obj(std::string &path) {
    std::ifstream file;
    file.open(path);

    size_t vertex_count = 0;
    size_t face_count = 0;

    string line;
    while (std::getline(file, line)) {
        if (line[0] == 'v') {
            vertex_count++;
        }
        else if(line[0] == 'f') {
            face_count++;
        }
    }

    vertex *verteces = vertex[vertex_count];
    size_t vi = 0;

    file.clear();
    file.seekg(0, ios::beg);

    while(std::getline(file, line)) {
        if(line[0] == 'v') {
            vertex v = verteces[vi++];
            sscanf("v %d %d %d", &v.x, &v.y, &v.z);
        }
        else if (line[0] == 'f') {

        }
    }
}
