cmake_minimum_required(VERSION 3.26.5)

project(out)

add_executable(${PROJECT_NAME}
    main.cpp
    http.cpp http.h
    socket.cpp socket.h
)