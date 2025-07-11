#include <string>
#include <vector>

struct vertex {
    float x;
    float y;
    float z;
};

struct triangle {
    vertex v1;
    vertex v2;
    vertex v3;
};

std::vector<triangle> load_obj(const std::string &path);
