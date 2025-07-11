#include <iostream>
#include <vector>
#include "terminal.h"
#include "wf_obj.h"

int main() {
	std::vector<triangle> triangles = load_obj("../test.obj");
	
	std::cout << "First vertex: " << triangles[0].v1.x << " " << triangles[0].v1.y << " " << triangles[0].v1.z << "\n";
}
