#include <iostream>
#include <limits>
#include <memory>
#include <vector>
#include "rasterizer.h"
#include "terminal.h"
#include "vertex_transformer.h"

int main() {
	std::cout << "Starting...\n";

	std::shared_ptr<Object> object = load_obj("../teapot.obj");

	object->translate({0, 0, -10});
	struct terminal_info ti = get_terminal_info();

	std::shared_ptr<std::vector<vertex>> trans_verteces = transform_perspective(object->verteces);

	ndc_to_window_cords(trans_verteces, ti.height, ti.width); 

	auto buffer = std::make_shared<std::vector<std::vector<Pixel>>>(ti.height, std::vector<Pixel>(ti.width, Pixel{{0, 0, 0, 0}, std::numeric_limits<float>::max()}));

	std::shared_ptr<std::vector<triangle>> triangles = filter_triangles(object->triangles, trans_verteces, ti.width	, ti.height);

	rasterize(buffer, trans_verteces, triangles);

	write_to_terminal(buffer);
}
