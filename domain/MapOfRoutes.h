//
// Created by mader on 15.02.2025.
//

#ifndef INFOTECS_TASK_3_MAPOFROUTES_H
#define INFOTECS_TASK_3_MAPOFROUTES_H

#include <iostream>
#include "map"

/**
 * Контейнерный класс для словаря со связками <сокращение> : <ссылка>
 */
class MapOfRoutes {
private:
    /**
     * Поле объекта словаря std::map
     */
    std::map<std::string, std::string> _routes;
public:
    /**
     * Добавление новой связки
     * @param abbr Сокращение
     * @param full Полная ссылка
     * @return true, если связки не было в словаре и она успешно добавлена
     */
    bool add_route(std::string abbr, std::string full);
    /**
     * Конвертация словарь в json
     * @return Словарь связок в json формате
     */
    std::string to_json();
    /**
     * Получение объекта словаря std::map
     * @return Объект словаря std::map
     */
    std::map<std::string, std::string> get_routes_obj();
};


#endif //INFOTECS_TASK_3_MAPOFROUTES_H
