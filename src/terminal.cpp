#include <iostream>
#include <memory>
#include <sys/ioctl.h>
#include <stdexcept>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <vector>

#include "terminal.h"

terminal_info get_terminal_info() {
    struct winsize w;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)) {
        throw std::runtime_error(std::string("An error occured while trying to get terminal info: ") + std::strerror(errno) + "\n");
    }
    struct terminal_info ti;
    ti.height = w.ws_row;
    ti.width = w.ws_col;
    return ti;
}



int write_to_terminal(std::shared_ptr<std::vector<std::vector<Pixel>>> buf){
	size_t height = buf->size();
	if (height == 0)
		return 0;
	size_t width = (*buf)[0].size();
	if (width == 0)
		return 0;

	char output[height * width + 8 + 1];
	strcpy(output, "\033[32m");
	size_t i = 0;
	for (auto row: (*buf)) {
		for (auto pix: row) {
			if (pix.color.a != 0) {
				output[i + 5] = '#';
			}
			else {
				output[i +5] = ' ';
			}
			i++;
		}
	}
	strcpy(output + i + 5, "\033[0m");

	std::cout << "\033[2J\033[1;1H";
	std::cout << output << "\n";

	return 0;
}

