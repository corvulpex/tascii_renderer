#ifndef TERMINAL_H
#define TERMINAL_H

#include <memory>
#include <vector>
struct Color {
	char r;
	char g;
	char b;
	char a;
};

struct Pixel {
	Color color;
	float depth;
};

struct terminal_info {
    unsigned short height;
    unsigned short width;
};

struct terminal_info get_terminal_info();

int write_to_terminal(std::shared_ptr<std::vector<std::vector<Pixel>>> buf);

#endif
