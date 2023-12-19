project(sockx-validation)

add_library(${PROJECT_NAME}
regex-validator.cpp regex-validator.h
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/..
)