project(sockx-network)

add_library(${PROJECT_NAME}
    servers/host.cpp servers/host.h
    sockets/sock.cpp sockets/sock.h
)
    
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/..
)