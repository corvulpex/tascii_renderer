#include "rasterizer.h"
#include "math_helper.h"
#include <Eigen/src/Core/Matrix.h>


int rasterize(std::shared_ptr<std::vector<std::vector<Pixel>>> screen_buffer, std::shared_ptr<std::vector<triangle>> triangles) {

	int buffer_height = screen_buffer->size();
	if (buffer_height == 0) 
		return 0;
	
	int buffer_width = (*screen_buffer)[0].size();
	if (buffer_width == 0)
		return 0;


	for (auto t: *triangles) {
		for (size_t h = 0; h < buffer_height; h++) {
			for (size_t w = 0; w < buffer_width; w++) {
				Eigen::Vector3f bc_cords = barycentric_coords(t, {(float) w + 0.5, (float) h + 0.5});
				
				if (bc_cords.x() + bc_cords.y() + bc_cords.z() > 1.0f)
					continue;

				float ip_z = bc_cords.x() * t.v1.pos.z() + bc_cords.y() * t.v2.pos.z() + bc_cords.z() * t.v3.pos.z();
				
				if (ip_z > (*screen_buffer)[h][w].depth)
					continue;


				(*screen_buffer)[h][w].depth = ip_z;	
				(*screen_buffer)[h][w].color = {static_cast<char>(255), 0, 0, static_cast<char>(255)};

			}
		}
	}

	return 0;
}

