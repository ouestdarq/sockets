project(sockx-hosts)

cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PROJECT_PARENT_DIR)

add_library(${PROJECT_NAME}
    host.cpp host.h
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_PARENT_DIR}
)

target_link_libraries(${PROJECT_NAME}
    sockx-core-requests
    sockx-core-socks
)
