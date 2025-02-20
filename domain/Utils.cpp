//
// Created by mader on 18.02.2025.
//

#include <random>
#include "Utils.h"
#include "Logger.h"

std::string Utils::generate_random_abbr(int length) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> main_distr(0, 2);

    std::uniform_int_distribution<> lower_chars_distr(97, 122);
    std::uniform_int_distribution<> upper_chars_distr(65, 90);
    std::uniform_int_distribution<> integers_distr(0, 9);

    std::string generated_abbr;
    for(int n = 0; n < length; ++n) {

        char generated_ch = 0;
        int generated_integer;

        int first_choice = main_distr(gen);

        switch (first_choice) {
            case 0:
                generated_ch = lower_chars_distr(gen);
                break;
            case 1:
                generated_ch = upper_chars_distr(gen);
                break;
            case 2:
                generated_integer = integers_distr(gen);
                break;
            default:
                break;
        }

        if (generated_ch != 0) {
            generated_abbr += generated_ch;
        } else {
            generated_abbr += std::to_string(generated_integer);
        }
    }
    return generated_abbr;
}

void Utils::set_redirector(httplib::Server &svr, Logger &lg, std::string abbr, std::string link) {
    svr.Get(abbr, [link](const httplib::Request &req, httplib::Response &res) {
        res.set_redirect(link);
    });
    lg.loading_log(abbr, "GET");
}


