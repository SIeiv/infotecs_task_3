#include <iostream>
#include <thread>

#include "httplib.h"
#include "domain/IO.h"
#include "domain/map_of_routes.h"
#include "domain/server_config.h"
#include "domain/logger.h"

using namespace httplib;

int main() {
    setlocale(LC_ALL, "Russian");

    server_config cfg;
    cfg.IP_ADDRESS = "127.0.0.1";
    cfg.PORT = 8080;
    cfg.PATH_TO_LINKS_FILE = "links.txt";

    /*std::map<std::string, std::string> routes;
    routes["/yandex"] = "https://ya.ru/";
    routes["/sex"] = "https://lk.pnzgu.ru/portfolio/517743476";*/

    /*std::ofstream out;          // поток для записи
    out.open("links.txt");      // открываем файл для записи
    if (out.is_open())
    {
        out << "Hello World!" << std::endl;
    }
    out.close();*/

    map_of_routes r;

    std::string line;

    std::ifstream in(cfg.PATH_TO_LINKS_FILE);
    if (in.is_open()) {
        while (std::getline(in, line)) {
            std::string abbr = line.substr(0, line.find(" : "));
            std::string full = line.substr(line.find(" : ") + 3);
            r.add_route(abbr, full);
        }
    }
    in.close();

    auto routes = r.get_routes_obj();

    Server svr;

    svr.set_logger([](const Request& req, const Response& res) {
        logger lg;
        lg.test_log(req, res);
    });

    svr.Get("/", [](const Request &req, Response &res) {
        res.set_content("Main Pages!", "text/plain");
    });

    svr.Post("/add_link", [](const Request &req, Response &res) {
        std::string val;
        if (req.has_param("key")) {
            val = req.get_param_value("key");
        }
        res.set_content(val, "text/plain");
    });


    for (const auto &[abbreviated, full]: routes) {
        svr.Get(abbreviated, [&full](const Request &req, Response &res) {
            res.set_redirect(full);
        });
    }

    /*std::thread io_thread([&r]() {
        IO io(r);
        io.show_initial_msg();
    });*/

    std::cout << "Server started on origin: http://" << cfg.IP_ADDRESS << ":" << cfg.PORT << std::endl;
    //printf("Server started on origin: http://%s:%i \n\n", cfg.IP_ADDRESS, cfg.PORT);
    svr.listen(cfg.IP_ADDRESS, cfg.PORT);
    //server_thread.join();


}
