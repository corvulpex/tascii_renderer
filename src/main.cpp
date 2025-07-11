#include <iostream>
#include <memory>
#include <vector>
#include "terminal.h"
#include "vertex_transformer.h"

int main() {
	std::shared_ptr<std::vector<triangle>> triangles = load_obj("../test.obj");

	transform_perspective(triangles);
	
	std::cout << "First vertex:\n" << (*triangles)[0].v1.pos << "\n";
}
