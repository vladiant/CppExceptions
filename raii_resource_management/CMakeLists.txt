cmake_minimum_required(VERSION 3.22)

project(raii_resource_management)

add_executable(
    ${PROJECT_NAME}
    raii_resource_management.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
