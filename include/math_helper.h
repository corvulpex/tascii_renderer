#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include "wf_obj.h"
#include <Eigen/Eigen>
#include <Eigen/src/Core/Matrix.h>


float triangle_area(Eigen::Vector2f v1, Eigen::Vector2f v2, Eigen::Vector2f v3); 

Eigen::Vector3f barycentric_coords(const triangle &t, Eigen::Vector2f p);

bool all_verteces_out_of_range(const triangle &t, float l, float h);

float map_num_from_range_to_range(float n, float a, float b, float c, float d);

Eigen::Vector4f triangle_bounding_box(triangle &t);

#endif
