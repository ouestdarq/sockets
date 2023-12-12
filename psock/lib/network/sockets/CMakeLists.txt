cmake_minimum_required(VERSION 3.26.5)

project(network-core-sockets-host)

add_library(${PROJECT_NAME}
    host.cpp host.h
)
