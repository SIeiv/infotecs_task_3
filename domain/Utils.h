//
// Created by mader on 18.02.2025.
//

#ifndef INFOTECS_TASK_3_UTILS_H
#define INFOTECS_TASK_3_UTILS_H


#include <string>
#include "../httplib.h"
#include "Logger.h"

/**
 * Класс с функциями помощниками
 */
class Utils {
public:
    /**
     * Генерация случайного сокращения
     * @param length Длина сокращения
     * @return Случайное сокращение заданной длины
     */
    static std::string generate_random_abbr(int length);
    /**
     * Инициализация нового роута с редиректом
     * @param svr Объект сервера (httplib::Server)
     * @param lg Объект логгера
     * @param abbr Сокращение ссылки
     * @param link Полная ссылка
     */
    static void set_redirector(httplib::Server &svr, Logger &lg, std::string abbr, std::string link);
};


#endif //INFOTECS_TASK_3_UTILS_H
