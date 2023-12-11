cmake_minimum_required(VERSION 3.26.5)

project(core)

add_library(${PROJECT_NAME}
    ./src/client.cpp
    ./src/host.cpp
    ./src/http.cpp ./src/http.h
    ./src/socket.cpp ./src/socket.h
)
