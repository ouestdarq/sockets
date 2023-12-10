cmake_minimum_required(VERSION 3.26.5)

project(out)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
    ./src/http.cpp ./src/http.h
    ./src/socket.cpp ./src/socket.h
)