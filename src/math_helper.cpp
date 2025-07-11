#include "math_helper.h"
#include "wf_obj.h"
#include <Eigen/src/Core/Matrix.h>
#include <algorithm>
#include <cstdlib>
#include <limits>

float triangle_area(Eigen::Vector2f v1, Eigen::Vector2f v2, Eigen::Vector2f v3) {
	return 0.5 * std::abs((v1.x() * (v2.y() - v3.y()) + v2.x() * (v3.y() - v1.y()) +  v3.x() * (v1.y() - v2.y())));
}




Eigen::Vector3f barycentric_coords(const triangle &t, Eigen::Vector2f p) {
	float t_area = triangle_area({t.v1.pos.x(), t.v1.pos.y()}, {t.v2.pos.x(), t.v2.pos.y()}, {t.v3.pos.x(), t.v3.pos.y()});
	if (t_area == 0) {
		return {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
	}
	float p12_area = triangle_area({p.x(), p.y()}, {t.v1.pos.x(), t.v1.pos.y()}, {t.v2.pos.x(), t.v2.pos.y()});
	float p23_area = triangle_area({p.x(), p.y()}, {t.v2.pos.x(), t.v2.pos.y()}, {t.v3.pos.x(), t.v3.pos.y()});
	float p31_area = triangle_area({p.x(), p.y()}, {t.v3.pos.x(), t.v3.pos.y()}, {t.v1.pos.x(), t.v1.pos.y()});


	return {p23_area / t_area, p31_area / t_area, p12_area / t_area};
}



bool all_verteces_out_of_range(const triangle &t, float l, float h) {

	bool b_v1_x = t.v1.pos.x() < l || t.v1.pos.x() > h; 
	bool b_v1_y = t.v1.pos.y() < l || t.v1.pos.y() > h; 
	bool b_v2_x = t.v2.pos.x() < l || t.v2.pos.x() > h; 
	bool b_v2_y = t.v2.pos.y() < l || t.v2.pos.y() > h; 
	bool b_v3_x = t.v3.pos.x() < l || t.v3.pos.x() > h; 
	bool b_v3_y = t.v3.pos.y() < l || t.v3.pos.y() > h; 

	return (b_v1_x || b_v1_y) && (b_v2_x || b_v2_y) && (b_v3_x || b_v3_y);
}


float map_num_from_range_to_range(float n, float a, float b, float c, float d) {
	return c + ((d - c) / (b - a))* (n - a);
}


Eigen::Vector4f triangle_bounding_box(triangle &t) {
	float x_min = std::min({t.v1.pos.x(), t.v2.pos.x(), t.v3.pos.x()});
	float y_min = std::min({t.v1.pos.y(), t.v2.pos.y(), t.v3.pos.y()});
	float x_max = std::max({t.v1.pos.x(), t.v2.pos.x(), t.v3.pos.x()});
	float y_max = std::max({t.v1.pos.y(), t.v2.pos.y(), t.v3.pos.y()});
	return {x_min, y_min, x_max, y_max};
}

