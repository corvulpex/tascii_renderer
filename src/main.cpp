#include <iostream>
#include <limits>
#include <memory>
#include <vector>
#include "object.h"
#include "rasterizer.h"
#include "terminal.h"
#include "vertex_transformer.h"

int main() {
	std::cout << "Starting...\n";

	std::shared_ptr<std::vector<triangle>> triangles = load_obj("../teapot.obj");

	std::cout << "Loaded object\n";

	auto obj = new Object(triangles);

	obj->translate({0, 0, -10});
	struct terminal_info ti = get_terminal_info();

	transform_perspective(triangles);

	std::cout << "Transformed perspective\n";

	std::shared_ptr<std::vector<triangle>> window_triangles = ndc_to_window_cords(triangles, ti.height, ti.width); 
	std::cout << "Mapped to window coordinates\n";
	std::cout << "Triangle count: " << (*triangles).size() << "\n";
 
	auto buffer = std::make_shared<std::vector<std::vector<Pixel>>>(ti.height, std::vector<Pixel>(ti.width, Pixel{{0, 0, 0, 0}, std::numeric_limits<float>::max()}));

	rasterize(buffer, window_triangles);
	std::cout << "Rasterized\n";
	

	write_to_terminal(buffer);
}
