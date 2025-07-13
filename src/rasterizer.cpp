#include "rasterizer.h"
#include "math_helper.h"
#include <Eigen/src/Core/Matrix.h>
#include <algorithm>

int rasterize(std::shared_ptr<std::vector<std::vector<Pixel>>> screen_buffer, std::shared_ptr<std::vector<vertex>> verteces, std::shared_ptr<std::vector<triangle>> triangles) {

	int buffer_height = screen_buffer->size();
	if (buffer_height == 0) 
		return 0;
	
	int buffer_width = (*screen_buffer)[0].size();
	if (buffer_width == 0)
		return 0;

	std::vector<vertex> vx = *verteces;

	for (auto t: *triangles) {
		Eigen::Vector4f bb = triangle_bounding_box(vx[t.v1], vx[t.v2], vx[t.v3]);
		for (size_t h = std::max(0, static_cast<int>(bb.y())); h < std::min(buffer_height, static_cast<int>(bb.w() + 1.0f)); h++) {
			for (size_t w = std::max(0, static_cast<int>(bb.x())); w < std::min(buffer_width, static_cast<int>(bb.z() + 1.0f)); w++) {
				Eigen::Vector3f bc_cords = barycentric_coords(vx[t.v1], vx[t.v2], vx[t.v3], {(float) w + 0.5, (float) h + 0.5});
				
				if (bc_cords.x() + bc_cords.y() + bc_cords.z() > 1.0f)
					continue;

				float ip_z = bc_cords.x() * vx[t.v1].pos.z() + bc_cords.y() * vx[t.v2].pos.z() + bc_cords.z() * vx[t.v3].pos.z();
				
				if (ip_z > (*screen_buffer)[h][w].depth)
					continue;


				(*screen_buffer)[h][w].depth = ip_z;	
				(*screen_buffer)[h][w].color = {static_cast<char>(255), 0, 0, static_cast<char>(255)};
				
			}
		}
	}

	return 0;
}

