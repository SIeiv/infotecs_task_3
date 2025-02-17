//
// Created by mader on 15.02.2025.
//

#include <iostream>
#include "IO.h"

void IO::show_initial_msg() {
    std::cout << "=====[Commands]=====" << std::endl;
    std::cout << "1. Add new link" << std::endl;
    std::cout << "2. Show existed links" << std::endl;
    input = std::cin.get();
    continuer();
}

void IO::run() {
    while (true) {
        show_initial_msg();
    }
}

void IO::continuer() {
    if (input == "1") {
        type = IO_action_types::add_new_link;
    } else if (input == "2") {
        std::cout << "=====[Links]=====" << std::endl;
        _routes.print_routes();
        show_initial_msg();
    }
}

IO::IO(map_of_routes routes) {
    type = IO_action_types::initial;
    _routes = routes;
}
