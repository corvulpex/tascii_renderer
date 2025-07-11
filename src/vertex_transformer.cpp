#include "vertex_transformer.h"
#include "math_helper.h"
#include "wf_obj.h"
#include <Eigen/Eigen>
#include <Eigen/src/Core/Matrix.h>
#include <memory>
#include <vector>
#include "math_helper.h"

const Eigen::Matrix4f perspective_matrix {
	{view_frustrum.n, 0, 0, 0},
	{0, view_frustrum.n, 0, 0},
	{0, 0, view_frustrum.n + view_frustrum.f, -1 * view_frustrum.n * view_frustrum.f},
	{0, 0, 1, 0}
};

const Eigen::Matrix4f normalizing_matrix {
	{2 / (view_frustrum.r - view_frustrum.l), 0, 0, (-1 * (view_frustrum.r + view_frustrum.l)) / (view_frustrum.r - view_frustrum.l)},
	{0, 2 / (view_frustrum.t - view_frustrum.b), 0, (-1 * (view_frustrum.t + view_frustrum.b)) / (view_frustrum.t - view_frustrum.b)},
	{0, 0, 2 / (view_frustrum.f - view_frustrum.n), (-1 * (view_frustrum.f + view_frustrum.n)) / (view_frustrum.f - view_frustrum.n)},
	{0, 0, 0, 1}
};

const Eigen::Matrix4f pp_matrix = normalizing_matrix * perspective_matrix;


void transform_perspective(std::shared_ptr<std::vector<triangle>> triangles) {

	for (auto &t: *triangles) {
		t.v1.pos = (perspective_matrix * t.v1.pos);
		t.v1.pos = (normalizing_matrix * t.v1.pos);
		t.v1.pos /= t.v1.pos.w();
		t.v2.pos = (pp_matrix * t.v2.pos);	
		t.v2.pos /= t.v2.pos.w();
		t.v3.pos = (pp_matrix * t.v3.pos);	
		t.v3.pos /= t.v3.pos.w();
	}

}

std::shared_ptr<std::vector<triangle>> ndc_to_window_cords(std::shared_ptr<std::vector<triangle>> triangles, size_t window_height, size_t window_width) {
	auto ndc_triangles = std::make_shared<std::vector<triangle>>();
	for (auto &t: *triangles) {
		if (all_verteces_out_of_range(t, -1.0, 1.0))
			continue;

		triangle transformed_triangle;

		
		transformed_triangle.v1.pos = {map_num_from_range_to_range(t.v1.pos.x(), -1.0, 1.0, 0, window_width),map_num_from_range_to_range(t.v1.pos.y(), -1.0, 1.0, 0, window_height), t.v1.pos.z(), 0};
	  	transformed_triangle.v2.pos = {map_num_from_range_to_range(t.v1.pos.x(), -1.0, 1.0, 0, window_width), map_num_from_range_to_range(t.v1.pos.y(), -1.0, 1.0, 0, window_height), t.v1.pos.z(), 0};
	  	transformed_triangle.v3.pos = {map_num_from_range_to_range(t.v1.pos.x(), -1.0, 1.0, 0, window_width), map_num_from_range_to_range(t.v1.pos.y(), -1.0, 1.0, 0, window_height), t.v1.pos.z(), 0};
		
		
		ndc_triangles->push_back(transformed_triangle);

	}

	return ndc_triangles;
}


