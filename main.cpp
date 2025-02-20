#include <iostream>

#include "httplib.h"
#include "domain/MapOfRoutes.h"
#include "domain/ServerConfig.h"
#include "domain/Utils.h"

int main()
{
    // Конфигурация сервера
    ServerConfig::IP_ADDRESS = "127.0.0.1";
    ServerConfig::PORT = 8080;
    ServerConfig::PATH_TO_LINKS_FILE = "links.txt";

    // Словарь сокращений
    MapOfRoutes r;

    // Читаем сокращения из текстового файла
    std::string line;
    std::ifstream in(ServerConfig::PATH_TO_LINKS_FILE);
    if (in.is_open()) {
        while (std::getline(in, line)) {
            std::string abbr = line.substr(0, line.find(" : "));
            std::string full = line.substr(line.find(" : ") + 3);
            r.add_route(abbr, full);
        }
    }
    in.close();

    auto routes = r.get_routes_obj();

    httplib::Server svr;
    Logger lg;

    lg.start_loading_log();

    // Логгер
    svr.set_logger([&lg](const httplib::Request &req, const httplib::Response &res) {
        lg.request_log(req, res);
    });

    // Главный роут
    svr.Get("/", [&svr](const httplib::Request &req, httplib::Response &res) {
        res.set_content("Main Page!", "text/plain");
    });
    lg.loading_log("/", "GET");

    // Роут с получением всех сокращений и их ссылок
    svr.Get("/get_links", [&svr, &r](const httplib::Request &req, httplib::Response &res) {
        res.set_content(r.to_json(), "application/json");
    });
    lg.loading_log("/get_links", "GET");

    // Роут добавления нового сокращения
    svr.Post("/add_link", [&r, &svr, &lg](const httplib::Request &req, httplib::Response &res) {
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

        if (r.add_route(abbr_val, link_val)) {
            Utils::set_redirector(svr, lg, abbr_val, link_val);

            std::ofstream vmdelet_out;
            vmdelet_out.open(ServerConfig::PATH_TO_LINKS_FILE,
                             std::ios::app);
            vmdelet_out << "\n" << abbr_val << " : " << link_val;
            vmdelet_out.close();
            res.body = "Link added: " + abbr_val;
        } else {
            res.status = httplib::StatusCode::BadRequest_400;
            res.body = "Link already exist!";
            lg.request_error("Link already exist!");
        }


    });
    lg.loading_log("/add_link", "POST");

    // Достаем связки из словаря
    for (const auto &[abbreviated, full]: routes) {
        Utils::set_redirector(svr, lg, abbreviated, full);
    }

    // Обработчик исключений
    svr.set_exception_handler([&lg](const auto& req, auto& res, std::exception_ptr ep) {
        std::string fmt = "<h1>Error 500</h1><p>%s</p>";
        try {
            std::rethrow_exception(ep);
        } catch (std::exception &e) {
            lg.exception(e.what());
        } catch (...) {
            lg.exception("Unknown Exception");
        }
        res.set_content(fmt, "text/html");
        res.status = httplib::StatusCode::InternalServerError_500;
    });

    // Старт сервера
    lg.loaded_log();
    svr.listen(ServerConfig::IP_ADDRESS, ServerConfig::PORT);
}
