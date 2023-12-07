cmake_minimum_required(VERSION 3.26.5)

project(sysock)

add_executable(${PROJECT_NAME}
    main.cpp
    socket.cpp socket.h
)
