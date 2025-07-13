#ifndef VERTEX_TRANSFORMER_H
#define VERTEX_TRANSFORMER_H

#include "wf_obj.h"
#include <memory>
#include <vector>

const struct {
	float n = 1.0;
	float f = 50.0;
	float l = -1;
	float r = 1;
	float b = -0.5;
	float t = 0.5;
} view_frustrum;


std::shared_ptr<std::vector<vertex>> transform_perspective(std::shared_ptr<const std::vector<vertex>> verteces);

void ndc_to_window_cords(std::shared_ptr<std::vector<vertex>> verteces, size_t window_height, size_t window_width);

std::shared_ptr<std::vector<triangle>> filter_triangles(std::shared_ptr<std::vector<triangle>> triangles, std::shared_ptr<std::vector<vertex>> verteces, int width, int height);

#endif
