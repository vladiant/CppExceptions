cmake_minimum_required(VERSION 3.22)

project(retrying_without_exceptions)

add_executable(
    ${PROJECT_NAME}
    retrying_without_exceptions.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
