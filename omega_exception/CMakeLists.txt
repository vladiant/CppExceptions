cmake_minimum_required(VERSION 3.22)

project(omega_exception)

add_executable(
    ${PROJECT_NAME}
    omega_exception.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
