#include <iostream>
#include "terminal.h"

int main() {
    struct terminal_info ti;
    ti = get_terminal_info();
    std::cout << "Height: " << ti.height << " Width: " << ti.width << "  \n";
}
