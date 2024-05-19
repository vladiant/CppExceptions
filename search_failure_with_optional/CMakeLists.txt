cmake_minimum_required(VERSION 3.22)

project(search_failure_with_optional)

add_executable(
    ${PROJECT_NAME}
    search_failure_with_optional.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
