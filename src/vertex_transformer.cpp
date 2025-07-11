#include "vertex_transformer.h"
#include <Eigen/Eigen>
#include <Eigen/src/Core/Matrix.h>
#include <iostream>
#include <memory>
#include <vector>


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

	std::cout << "Transforming\n";
	for (auto &t: *triangles) {
		std::cout << t.v1.pos << "\n";
		std::cout << "perspective matrix:\n" << perspective_matrix << "\n";
		t.v1.pos = (perspective_matrix * t.v1.pos);
		std::cout << "after perspective:\n" << t.v1.pos << "\n";
		t.v1.pos = (normalizing_matrix * t.v1.pos);
		std::cout << "after normalizing:\n" << t.v1.pos << "\n";
		t.v1.pos /= t.v1.pos.w();
		t.v2.pos = (pp_matrix * t.v2.pos);	
		t.v2.pos /= t.v2.pos.w();
		t.v3.pos = (pp_matrix * t.v3.pos);	
		t.v3.pos /= t.v3.pos.w();
	}

}
