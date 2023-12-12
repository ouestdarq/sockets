cmake_minimum_required(VERSION 3.26.5)

project(pm-network-requests)

add_library(${PROJECT_NAME}
    http.cpp http.h
)
