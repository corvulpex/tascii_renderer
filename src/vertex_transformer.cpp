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


std::shared_ptr<std::vector<vertex>> transform_perspective(std::shared_ptr<const std::vector<vertex>> verteces) {
	auto transformed_verteces = std::make_shared<std::vector<vertex>>(verteces->size());
	
	for (size_t i = 0; i < verteces->size(); i++) {
		(*transformed_verteces)[i].pos = (pp_matrix * (*verteces)[i].pos);
		(*transformed_verteces)[i].pos /= (*transformed_verteces)[i].pos.w();
		(*transformed_verteces)[i].color = (*verteces)[i].color;
		(*transformed_verteces)[i].normal = (*verteces)[i].normal;
	} 
	return transformed_verteces;
}

void ndc_to_window_cords(std::shared_ptr<std::vector<vertex>> verteces, size_t window_height, size_t window_width) {
	for (auto &v: *verteces) {
		v.pos = {map_num_range(v.pos.x(), -1.0, 1.0, 0, window_width),map_num_range(v.pos.y(), -1.0, 1.0, 0, window_height), v.pos.z(), 0};
	}
}


std::shared_ptr<std::vector<triangle>> filter_triangles(std::shared_ptr<std::vector<triangle>> triangles, std::shared_ptr<std::vector<vertex>> verteces, int width, int height) {
	auto vx = *verteces;
	auto ft = std::make_shared<std::vector<triangle>>();
	for (auto t: *triangles) {
		if (!all_verteces_out_of_range(vx[t.v1], vx[t.v2], vx[t.v3], 0.5, 0.5, (float) width - 0.5, (float) height - 0.5)) {
			ft->push_back(t);
		}
	}
	return ft;
}
