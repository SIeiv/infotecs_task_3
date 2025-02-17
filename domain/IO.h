//
// Created by mader on 15.02.2025.
//

#ifndef INFOTECS_TASK_3_IO_H
#define INFOTECS_TASK_3_IO_H

#include "IO_action_types.h"
#include "map_of_routes.h"

class IO {
private:
    std::string input;
    map_of_routes _routes;
    IO_action_types type;
    void continuer();
public:
    IO(map_of_routes routes);

    void show_initial_msg();
    void run();


};


#endif //INFOTECS_TASK_3_IO_H
