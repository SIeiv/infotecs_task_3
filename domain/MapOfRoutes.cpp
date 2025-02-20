//
// Created by mader on 15.02.2025.
//

#include "MapOfRoutes.h"

bool MapOfRoutes::add_route(std::string abbr, std::string full) {
    if (!_routes.count(abbr)) {
        _routes[abbr] = full;
        return true;
    }
    return false;
}

std::map<std::string, std::string> MapOfRoutes::get_routes_obj() {
    return _routes;
}

std::string MapOfRoutes::to_json() {
    std::string json = "{";
    for (const auto &[abbreviated, full]: _routes) {
        json.append("\"" + abbreviated + "\":\"" + full + "\",");
    }
    json.pop_back();
    json.append("}");
    return json;
}
