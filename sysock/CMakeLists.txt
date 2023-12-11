cmake_minimum_required(VERSION 3.26.5)

project(out)

add_subdirectory(./ext/dstrct)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
    ./src/http.cpp ./src/http.h
    ./src/socket.cpp ./src/socket.h
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ./ext/dstrct
)

target_link_directories(${PROJECT_NAME} 
    PRIVATE 
        ./ext/dstrct
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        dstrct
)
