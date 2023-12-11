cmake_minimum_required(VERSION 3.26.5)

project(out)

add_subdirectory(./ext/dstrct)

add_subdirectory(./core)


add_executable(${PROJECT_NAME}
    ./src/main.cpp
)


target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ./core/src
        ./ext/dstrct/src
)

target_link_directories(${PROJECT_NAME} 
    PRIVATE 
    ./core/src
    ./ext/dstrct/src
    )

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        core
        dstrct
)
