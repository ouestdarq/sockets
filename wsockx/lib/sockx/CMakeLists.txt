cmake_minimum_required(VERSION 3.26.5)

project(sockx)

add_subdirectory(core)

add_library(${PROJECT_NAME}
    socks/host.cpp socks/host.h
)

target_link_libraries(${PROJECT_NAME}
    sockx-core-requests
    sockx-core-socks
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)
# project(sockx-hosts)

# cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PROJECT_PARENT_DIR)

# add_library(${PROJECT_NAME}
#     host.cpp host.h
# )


# target_link_libraries(${PROJECT_NAME}
#     PRIVATE
#         sockx-core-requests
#         sockx-core-socks
# )
