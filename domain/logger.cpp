//
// Created by mader on 17.02.2025.
//

#include "logger.h"
#include "server_config.h"

void logger::start_loading_log() {
    printf("[LOG] Loading...\n");
}

void logger::request_log(const httplib::Request &req, const httplib::Response &res) {

    _count++;
    printf("[LOG] |Request_%i| Method: %s | Path: %s\n", _count, req.method.c_str(), req.path.c_str());
    printf("[LOG] |Response_%i| Status: %i\n", _count, res.status);

    /*s += "================================\n";

    snprintf(buf, sizeof(buf), "%s %s %s", req.method.c_str(),
             req.version.c_str(), req.path.c_str());
    s += buf;

    std::string query;
    for (auto it = req.params.begin(); it != req.params.end(); ++it) {
        const auto &x = *it;
        snprintf(buf, sizeof(buf), "%c%s=%s",
                 (it == req.params.begin()) ? '?' : '&', x.first.c_str(),
                 x.second.c_str());
        query += buf;
    }
    snprintf(buf, sizeof(buf), "%s\n", query.c_str());
    s += buf;

    s += dump_headers(req.headers);

    s += "--------------------------------\n";

    snprintf(buf, sizeof(buf), "%d %s\n", res.status, res.version.c_str());
    s += buf;
    s += dump_headers(res.headers);
    s += "\n";

    if (!res.body.empty()) { s += res.body; }

    s += "\n";

    return s;*/
}

void logger::request_warn(std::string msg) {
    printf("[WARN] in Request_%i: %s\n", _count + 1, msg.c_str());
}

void logger::loading_log(std::string pattern, std::string method) {
    printf("[LOG] Route \"%s\" initialized with %s method\n", pattern.c_str(), method.c_str());
}

void logger::loaded_log() {
    std::cout << "[LOG] Server started on origin: http://" << server_config::IP_ADDRESS
              << ":" << server_config::PORT << std::endl;
}
