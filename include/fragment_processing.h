#ifndef FRAGMENT_PROCESSING_H
#define FRAGMENT_PROCESSING_H

#include "terminal.h"
#include <Eigen/Eigen>
#include <memory>
#include <vector>

struct Fragment {
	Eigen::Vector4f color;
	Eigen::Vector3f normal;
	float depth;
};

std::shared_ptr<std::vector<std::vector<Pixel>>> fragment_shadering(terminal_info ti, std::shared_ptr<std::vector<std::vector<Fragment>>> fragments);

#endif 
