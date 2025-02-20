//
// Created by mader on 17.02.2025.
//

#ifndef INFOTECS_TASK_3_LOGGER_H
#define INFOTECS_TASK_3_LOGGER_H

#include "httplib.h"
#include "ServerConfig.h"


/**
 * Логгирует действия сервера
 */
class Logger {
private:
    /**
     * Счётчик запросов
     */
    static inline int _count = 0;
    /**
     * Получение текущего времени
     * @return время в формате <день_недели> <месяц> <число> чч:мм:сс <год>
     */
    static char* get_current_time();
public:
    /**
     * Лог начала загрузки сервера
     */
    void start_loading_log();
    /**
     * Лог начала загрузки сервера
     */
    void loading_log(std::string pattern, std::string method);
    /**
     * Лог начала загрузки сервера
     * @param req Объект запроса
     * @param res Объект ответа
     */
    void request_log(const httplib::Request &req, const httplib::Response &res);
    /**
     * Лог ошибки запроса
     * @param msg Сообщение ошибки
     */
    void request_error(std::string msg);
    /**
     * Лог исключения
     * @param msg Сообщение исключения
     */
    void exception(std::string msg);
    /**
     * Лог конца загрузки сервера
     */
    void loaded_log();
};


#endif //INFOTECS_TASK_3_LOGGER_H
