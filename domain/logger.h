//
// Created by mader on 17.02.2025.
//

#ifndef INFOTECS_TASK_3_LOGGER_H
#define INFOTECS_TASK_3_LOGGER_H

#include "httplib.h"

class logger {
private:
    std::string dump_headers(const httplib::Headers &headers);
    static inline int _count = 0;
public:

    void test_log(const httplib::Request &req, const httplib::Response &res);
};


#endif //INFOTECS_TASK_3_LOGGER_H
