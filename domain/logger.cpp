//
// Created by mader on 17.02.2025.
//

#include "Logger.h"

void Logger::start_loading_log() {
    printf("[LOG] Loading...\n");
}

void Logger::request_log(const httplib::Request &req, const httplib::Response &res) {
    _count++;
    printf("[LOG] %s |Request_%i| Method: %s | Path: %s\n", get_current_time() , _count, req.method.c_str(), req.path.c_str());
    printf("[LOG] %s |Response_%i| Status: %i\n", get_current_time(), _count, res.status);

}

void Logger::request_error(std::string msg) {
    printf("[ERROR] %s in Request_%i: %s\n", get_current_time(), _count + 1, msg.c_str());
}

void Logger::exception(std::string msg) {
    printf("[ERROR] %s %s\n", get_current_time(), msg.c_str());
}

void Logger::loading_log(std::string pattern, std::string method) {
    printf("[LOG] %s Route \"%s\" initialized with %s method\n", get_current_time() ,pattern.c_str(), method.c_str());

}

void Logger::loaded_log() {
    std::cout << "[LOG] " << get_current_time() << " Server started on origin: http://" << ServerConfig::IP_ADDRESS
              << ":" << ServerConfig::PORT << std::endl;
}

char* Logger::get_current_time() {
    time_t _time = std::time(nullptr);
    tm* _localtime = std::localtime(&_time);
    char* _asctime = std::asctime(_localtime);
    return _asctime;
}
