#ifndef VERTEX_TRANSFORMER_H
#define VERTEX_TRANSFORMER_H

#include "wf_obj.h"
#include <memory>
#include <vector>

const struct {
	float n = 1.0;
	float f = 50.0;
	float l = -0.5;
	float r = 0.5;
	float b = -0.5;
	float t = 0.5;
} view_frustrum;


void transform_perspective(std::shared_ptr<std::vector<triangle>> triangles);


std::shared_ptr<std::vector<triangle>> ndc_to_window_cords(std::shared_ptr<std::vector<triangle>> triangles, size_t window_height, size_t window_width);

#endif
