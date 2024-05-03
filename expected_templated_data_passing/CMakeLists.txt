cmake_minimum_required(VERSION 3.22)

project(expected_templated_data_passing)

add_executable(
    ${PROJECT_NAME}
    expected_templated_data_passing.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
