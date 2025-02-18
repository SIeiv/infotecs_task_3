#include <iostream>
#include <thread>

#include "httplib.h"
#include "domain/map_of_routes.h"
#include "domain/server_config.h"
#include "domain/logger.h"
#include "domain/Utils.h"

using namespace httplib;

int main() {
    //setlocale(LC_ALL, "Russian");

    server_config::IP_ADDRESS = "127.0.0.1";
    server_config::PORT = 8080;
    server_config::PATH_TO_LINKS_FILE = "links.txt";

    map_of_routes r;

    std::string line;

    std::ifstream in(server_config::PATH_TO_LINKS_FILE);
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
    logger lg;

    lg.start_loading_log();

    svr.set_logger([&lg](const Request &req, const Response &res) {
        lg.request_log(req, res);
    });

    svr.Get("/", [&svr](const Request &req, Response &res) {
        res.set_content("Main Pages!", "text/plain");
    });
    lg.loading_log("/", "GET");

    svr.Post("/add_link", [&r, &svr, &lg](const Request &req, Response &res) {
        std::string link_val;
        std::string abbr_val;

        if (req.has_param("link")) {
            link_val = req.get_param_value("link");
        }
        if (req.has_param("abbr")) {
            abbr_val = "/" + req.get_param_value("abbr");
        } else {
            abbr_val = "/" + Utils::generate_random_abbr(16);
        }

        //тут надо проверку на уже наличие такого сокращения в словаре надо!!!

        if (r.add_route(abbr_val, link_val)) {
            svr.Get(abbr_val, [link_val](const Request &req, Response &res) {
                res.set_redirect(link_val);
            });
            lg.loading_log(abbr_val, "GET");

            std::ofstream vmdelet_out;                    //создаем поток
            vmdelet_out.open(server_config::PATH_TO_LINKS_FILE,
                             std::ios::app);  // открываем файл для записи в конец// сама запись
            vmdelet_out << "\n" << abbr_val << " : " << link_val;
            vmdelet_out.close();
            res.body = "Success!";
        } else {
            res.status = 500;
            res.body = "Link already exist!";
            lg.request_warn("Link already exist!");
        }


    });
    lg.loading_log("/add_link", "POST");

    for (const auto &[abbreviated, full]: routes) {
        svr.Get(abbreviated, [&full](const Request &req, Response &res) {
            res.set_redirect(full);
        });
        lg.loading_log(abbreviated, "GET");
    }

    lg.loaded_log();
    svr.listen(server_config::IP_ADDRESS, server_config::PORT);


}
