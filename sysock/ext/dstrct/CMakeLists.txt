cmake_minimum_required(VERSION 3.26.5)

project(dstrct)

add_library(${PROJECT_NAME} INTERFACE
    lnlist.h
    node.h
)