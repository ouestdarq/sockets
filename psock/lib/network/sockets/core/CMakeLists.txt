cmake_minimum_required(VERSION 3.26.5)

project(network-core-socket)

add_library(${PROJECT_NAME}
    socket.cpp socket.h
)
