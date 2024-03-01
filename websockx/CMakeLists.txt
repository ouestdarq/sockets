cmake_minimum_required(VERSION 3.26.5)

project(out)

add_subdirectory(lib/sockx)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

# target_include_directories(${PROJECT_NAME}
#     PRIVATE
#         ./lib
# )

target_link_libraries(${PROJECT_NAME}
        sockx
)
