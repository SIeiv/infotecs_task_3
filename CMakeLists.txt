cmake_minimum_required(VERSION 3.30)
project(infotecs_task_3)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

FetchContent_Declare(httplib SYSTEM
        GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
        GIT_TAG a609330e4c6374f741d3b369269f7848255e1954 # v0.14.1
        GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(httplib)

add_executable(infotecs_task_3 main.cpp
        domain/MapOfRoutes.cpp
        domain/MapOfRoutes.h
        domain/ServerConfig.h
        domain/Logger.cpp
        domain/Logger.h
        domain/Utils.cpp
        domain/Utils.h
)
target_link_libraries(infotecs_task_3 PRIVATE httplib)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/links.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)




