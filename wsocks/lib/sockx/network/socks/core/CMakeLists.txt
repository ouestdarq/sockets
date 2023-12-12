cmake_minimum_required(VERSION 3.26.5)

project(pm-network-core-socks)

add_library(${PROJECT_NAME}
    sock.cpp sock.h
)
