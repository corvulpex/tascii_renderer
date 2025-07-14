#ifndef TERMINAL_H
#define TERMINAL_H

#include <Eigen/Eigen>
#include <memory>
#include <vector>

struct Pixel {
	Eigen::Vector4f color;
};

struct terminal_info {
    unsigned short height;
    unsigned short width;
};

struct terminal_info get_terminal_info();

int write_to_terminal(std::shared_ptr<std::vector<std::vector<Pixel>>> buf);

#endif
