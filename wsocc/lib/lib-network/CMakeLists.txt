cmake_minimum_required(VERSION 3.26.5)

project(network)

add_subdirectory(network/core)

add_subdirectory(network/request)

add_library(${PROJECT_NAME}
    network/host.cpp network/host.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

# target_link_directories(${PROJECT_NAME}
#     PUBLIC
#         ${PROJECT_SOURCE_DIR}
# )

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        network-core
        network-request
)