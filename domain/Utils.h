//
// Created by mader on 18.02.2025.
//

#ifndef INFOTECS_TASK_3_UTILS_H
#define INFOTECS_TASK_3_UTILS_H


#include <string>
#include "../httplib.h"
#include "logger.h"

class Utils {
public:
    static std::string generate_random_abbr(int length);
    static void set_redirector(httplib::Server &svr, logger &lg, std::string abbr, std::string link);
};


#endif //INFOTECS_TASK_3_UTILS_H
