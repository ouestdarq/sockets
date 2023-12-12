cmake_minimum_required(VERSION 3.26.5)

project(sockx)

add_subdirectory(core)

add_library(${PROJECT_NAME}
    socks/host.cpp socks/host.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    sockx-core-requests
    sockx-core-socks
)
