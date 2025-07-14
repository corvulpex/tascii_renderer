#include "fragment_processing.h"
#include "terminal.h"
#include <Eigen/src/Core/Matrix.h>
#include <cstddef>
#include <memory>
#include <vector>


std::shared_ptr<std::vector<std::vector<Pixel>>> fragment_shadering(terminal_info ti, std::shared_ptr<std::vector<std::vector<Fragment>>> fragments) {

	auto pixels = std::make_shared<std::vector<std::vector<Pixel>>>(ti.height, std::vector<Pixel>(ti.width, {Eigen::Vector4f{0, 0, 0, 0}}));

	for (size_t h = 0; h < ti.height; h++) {
		for (size_t w = 0; w < ti.width; w++) {
			Fragment fragment = (*fragments)[h][w];

			(*pixels)[h][w].color = fragment.color;
		}
	}

	return pixels;
}

