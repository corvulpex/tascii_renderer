#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include "wf_obj.h"
#include <Eigen/Eigen>
#include <Eigen/src/Core/Matrix.h>


float triangle_area(Eigen::Vector2f v1, Eigen::Vector2f v2, Eigen::Vector2f v3); 

Eigen::Vector3f barycentric_coords(vertex &v1, vertex &v2, vertex &v3, Eigen::Vector2f p);

bool all_verteces_out_of_range(const vertex &v1, const vertex &v2, const vertex &v3, float bx, float by, float tx, float ty);

float map_num_range(float n, float a, float b, float c, float d);

Eigen::Vector4f triangle_bounding_box(vertex &v1, vertex &v2, vertex &v3);

#endif
