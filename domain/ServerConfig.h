//
// Created by mader on 17.02.2025.
//

#ifndef INFOTECS_TASK_3_SERVERCONFIG_H
#define INFOTECS_TASK_3_SERVERCONFIG_H


#include <string>

/**
 * Конфигуратор сервера
 */
struct ServerConfig {
    /**
     * Поле ip адреса сервера
     */
    static inline std::string IP_ADDRESS;
    /**
     * Поле порта адреса сервера
     */
    static inline int PORT;
    /**
     * Поле пути с txt файлом для сохранения связок сокращений и ссылок
     */
    static inline std::string PATH_TO_LINKS_FILE;
};


#endif //INFOTECS_TASK_3_SERVERCONFIG_H
