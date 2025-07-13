#include "math_helper.h"
#include "wf_obj.h"
#include <Eigen/src/Core/Matrix.h>
#include <algorithm>
#include <cstdlib>
#include <limits>

float triangle_area(Eigen::Vector2f v1, Eigen::Vector2f v2, Eigen::Vector2f v3) {
	return 0.5 * std::abs((v1.x() * (v2.y() - v3.y()) + v2.x() * (v3.y() - v1.y()) +  v3.x() * (v1.y() - v2.y())));
}




Eigen::Vector3f barycentric_coords(vertex &v1, vertex &v2, vertex &v3, Eigen::Vector2f p) {
	float t_area = triangle_area({v1.pos.x(), v1.pos.y()}, {v2.pos.x(), v2.pos.y()}, {v3.pos.x(), v3.pos.y()});
	if (t_area == 0) {
		return {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
	}
	float p12_area = triangle_area({p.x(), p.y()}, {v1.pos.x(), v1.pos.y()}, {v2.pos.x(), v2.pos.y()});
	float p23_area = triangle_area({p.x(), p.y()}, {v2.pos.x(), v2.pos.y()}, {v3.pos.x(), v3.pos.y()});
	float p31_area = triangle_area({p.x(), p.y()}, {v3.pos.x(), v3.pos.y()}, {v1.pos.x(), v1.pos.y()});


	return {p23_area / t_area, p31_area / t_area, p12_area / t_area};
}



bool all_verteces_out_of_range(const vertex &v1, const vertex &v2, const vertex &v3, float bx, float by, float tx, float ty) {

	bool b_v1_x = v1.pos.x() < bx || v1.pos.x() > tx; 
	bool b_v1_y = v1.pos.y() < by || v1.pos.y() > ty; 
	bool b_v2_x = v2.pos.x() < bx || v2.pos.x() > tx;
	bool b_v2_y = v2.pos.y() < by || v2.pos.y() > ty; 
	bool b_v3_x = v3.pos.x() < bx || v3.pos.x() > tx; 
	bool b_v3_y = v3.pos.y() < by || v3.pos.y() > ty; 

	return (b_v1_x || b_v1_y) && (b_v2_x || b_v2_y) && (b_v3_x || b_v3_y);
}


float map_num_range(float n, float a, float b, float c, float d) {
	return c + ((d - c) / (b - a))* (n - a);
}


Eigen::Vector4f triangle_bounding_box(vertex &v1, vertex &v2, vertex &v3) {
	float x_min = std::min({v1.pos.x(), v2.pos.x(), v3.pos.x()});
	float y_min = std::min({v1.pos.y(), v2.pos.y(), v3.pos.y()});
	float x_max = std::max({v1.pos.x(), v2.pos.x(), v3.pos.x()});
	float y_max = std::max({v1.pos.y(), v2.pos.y(), v3.pos.y()});
	return {x_min, y_min, x_max, y_max};
}

