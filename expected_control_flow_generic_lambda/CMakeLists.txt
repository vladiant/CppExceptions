cmake_minimum_required(VERSION 3.22)

project(expected_control_flow_generic_lambda)

add_executable(
    ${PROJECT_NAME}
    expected_control_flow_generic_lambda.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
