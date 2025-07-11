#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "terminal.h"
#include "wf_obj.h"
#include <memory>
#include <vector>


int rasterize(std::shared_ptr<std::vector<std::vector<Pixel>>> screen_buffer, std::shared_ptr<std::vector<triangle>>);

#endif
