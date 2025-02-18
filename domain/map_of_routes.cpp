//
// Created by mader on 15.02.2025.
//

#include "map_of_routes.h"

bool map_of_routes::add_route(std::string abbr, std::string full) {
    if (!_routes.count(abbr)) {
        _routes[abbr] = full;
        return true;
    }
    return false;
}

std::map<std::string, std::string> map_of_routes::get_routes_obj() {
    return _routes;
}

void map_of_routes::print_routes() {
    for (const auto& [abbr, full] : _routes) {
        std::cout << abbr << " -> " << full << std::endl;
    }
}
