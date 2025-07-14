#include "rasterizer.h"
#include "math_helper.h"
#include <Eigen/src/Core/Matrix.h>
#include <algorithm>
#include <iostream>
#include <memory>

std::shared_ptr<std::vector<std::vector<Fragment>>> rasterize(terminal_info ti, std::shared_ptr<std::vector<vertex>> verteces, std::shared_ptr<std::vector<triangle>> triangles) {

	auto fragments = std::make_shared<std::vector<std::vector<Fragment>>>(ti.height, std::vector<Fragment>(ti.width, {Eigen::Vector4f{0.0f, 0.0f, 0.0f, 0.0f}, Eigen::Vector3f{0.0f, 0.0f, 0.0f}, std::numeric_limits<float>::max()}));

	std::vector<vertex> vx = *verteces;

	for (auto t: *triangles) {
		Eigen::Vector4f bb = triangle_bounding_box(vx[t.v1], vx[t.v2], vx[t.v3]);

		for (size_t h = std::max(0, static_cast<int>(bb.y())); h < std::min((int) ti.height, static_cast<int>(bb.w() + 1.0f)); h++) {
			for (size_t w = std::max(0, static_cast<int>(bb.x())); w < std::min((int) ti.width, static_cast<int>(bb.z() + 1.0f)); w++) {

				Eigen::Vector3f bc_cords = barycentric_coords(vx[t.v1], vx[t.v2], vx[t.v3], {(float) w + 0.5, (float) h + 0.5});
				
				if (bc_cords.x() + bc_cords.y() + bc_cords.z() > 1.0f)
					continue;

				float ip_z = bc_cords.x() * vx[t.v1].pos.z() + bc_cords.y() * vx[t.v2].pos.z() + bc_cords.z() * vx[t.v3].pos.z();
				
				if (ip_z > (*fragments)[h][w].depth)
					continue;


				(*fragments)[h][w].depth = ip_z;
				(*fragments)[h][w].color = bc_cords.x() * vx[t.v1].color + bc_cords.y() * vx[t.v2].color + bc_cords.z() * vx[t.v3].color;
				(*fragments)[h][w].normal = bc_cords.x() * vx[t.v1].normal + bc_cords.y() * vx[t.v2].normal + bc_cords.z() * vx[t.v3].normal;

			}
		}
	}

	return fragments;
}

