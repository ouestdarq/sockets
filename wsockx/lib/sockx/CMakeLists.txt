cmake_minimum_required(VERSION 3.26.5)

project(sockx-network)

add_subdirectory(network/core)

add_subdirectory(protocol)

add_library(${PROJECT_NAME}
    network/host.cpp network/host.h
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
        sockx-network-core
        sockx-protocol
)
