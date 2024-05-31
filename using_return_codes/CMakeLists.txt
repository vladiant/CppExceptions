cmake_minimum_required(VERSION 3.22)

project(using_return_codes)

add_executable(
    ${PROJECT_NAME}
    using_return_codes.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
