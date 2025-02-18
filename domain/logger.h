//
// Created by mader on 17.02.2025.
//

#ifndef INFOTECS_TASK_3_LOGGER_H
#define INFOTECS_TASK_3_LOGGER_H

#include "httplib.h"

class logger {
private:
    static inline int _count = 0;
public:
    void start_loading_log();
    void loading_log(std::string pattern, std::string method);
    void request_log(const httplib::Request &req, const httplib::Response &res);
    void request_warn(std::string msg);
    void loaded_log();
};


#endif //INFOTECS_TASK_3_LOGGER_H
