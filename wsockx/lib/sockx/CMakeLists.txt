cmake_minimum_required(VERSION 3.26.5)

project(sockx)

add_subdirectory(network)

add_subdirectory(protocol)

add_subdirectory(validation)


add_library(${PROJECT_NAME}
    server.h
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
        sockx-network
        sockx-protocol
        sockx-validation
)

