cmake_minimum_required(VERSION 3.10)

project(bad_resource_management)

add_executable(
    ${PROJECT_NAME}
    bad_resource_management.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
