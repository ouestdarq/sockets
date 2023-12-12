cmake_minimum_required(VERSION 3.26.5)

project(data-structs)

add_library(${PROJECT_NAME} INTERFACE
    linked-list.h
    node.h
    queue.h
)
