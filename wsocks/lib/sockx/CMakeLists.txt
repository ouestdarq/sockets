cmake_minimum_required(VERSION 3.26.5)

project(sockx)

add_subdirectory(sockx/requests)

add_subdirectory(sockx/socks/core)

add_library(${PROJECT_NAME}
    sockx/socks/host.cpp sockx/socks/host.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}

    PRIVATE
        ./sockx
)

target_link_libraries(${PROJECT_NAME}
    pm-sockx-requests
    pm-sockx-core-socks
)
