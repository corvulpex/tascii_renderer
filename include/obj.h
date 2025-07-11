#include <string>

struct vertex {
    float x;
    float y;
    float z;
}

struct triangle {
    vertex v1;
    vertex v2;
    vertex v3;
}

struct triangle* load_obj(std::string &path);
