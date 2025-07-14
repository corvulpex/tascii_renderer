#include <memory>
#include "fragment_processing.h"
#include "rasterizer.h"
#include "terminal.h"
#include "vertex_transformer.h"

int main() {
	std::shared_ptr<Object> object = load_obj("../teapot.obj");
	object->translate({0, 0, -10});

	struct terminal_info ti = get_terminal_info();

	auto trans_verteces = transform_perspective(object->verteces);
	ndc_to_window_cords(trans_verteces, ti.height, ti.width); 

	auto triangles = filter_triangles(object->triangles, trans_verteces, ti.width, ti.height);

	auto fragments = rasterize(ti, trans_verteces, triangles);

	auto pixels = fragment_shadering(ti, fragments);

	write_to_terminal(pixels);
}
