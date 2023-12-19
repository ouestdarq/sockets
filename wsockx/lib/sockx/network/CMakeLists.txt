project(sockx-network)

add_library(${PROJECT_NAME}
    core/sock.cpp core/sock.h
    host.cpp host.h
)
    
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/..
)