project(sockx-request)

add_library(${PROJECT_NAME}
    core/request.cpp core/request.h
    protocols/http.cpp protocols/http.h
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/..
)