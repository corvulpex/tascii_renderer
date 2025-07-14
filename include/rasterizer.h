#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "fragment_processing.h"
#include "terminal.h"
#include "wf_obj.h"
#include <Eigen/src/Core/Matrix.h>
#include <memory>
#include <vector>


std::shared_ptr<std::vector<std::vector<Fragment>>> rasterize(terminal_info ti, std::shared_ptr<std::vector<vertex>> verteces, std::shared_ptr<std::vector<triangle>> triangles);

#endif
