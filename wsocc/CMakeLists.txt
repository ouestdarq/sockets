cmake_minimum_required(VERSION 3.26.5)

project(out)

add_subdirectory(lib)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
)

# target_include_directories(${PROJECT_NAME}
#     PRIVATE
#         ./lib/data-structs
# )

target_link_libraries(${PROJECT_NAME}
        network
)
