#include <sys/ioctl.h>
#include <stdexcept>
#include <unistd.h>
#include <cerrno>
#include <cstring>

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
