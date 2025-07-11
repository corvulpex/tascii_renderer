#include <iostream>
#include <limits>
#include <memory>
#include <vector>
#include "rasterizer.h"
#include "terminal.h"
#include "vertex_transformer.h"

int main() {


	std::shared_ptr<std::vector<triangle>> triangles = load_obj("../test.obj");

	struct terminal_info ti = get_terminal_info();

	transform_perspective(triangles);

	std::shared_ptr<std::vector<triangle>> window_triangles = ndc_to_window_cords(triangles, ti.height, ti.width); 

	auto buffer = std::make_shared<std::vector<std::vector<Pixel>>>(ti.height, std::vector<Pixel>(ti.width, Pixel{{0, 0, 0, 0}, std::numeric_limits<float>::max()}));

	rasterize(buffer, window_triangles);
	

	write_to_terminal(buffer);
}
