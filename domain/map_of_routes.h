//
// Created by mader on 15.02.2025.
//

#ifndef INFOTECS_TASK_3_MAP_OF_ROUTES_H
#define INFOTECS_TASK_3_MAP_OF_ROUTES_H

#include <iostream>
#include "map"

class map_of_routes {
private:
    std::map<std::string, std::string> _routes;
public:
    bool add_route(std::string abbr, std::string full);
    void print_routes();

    std::map<std::string, std::string> get_routes_obj();
};


#endif //INFOTECS_TASK_3_MAP_OF_ROUTES_H
