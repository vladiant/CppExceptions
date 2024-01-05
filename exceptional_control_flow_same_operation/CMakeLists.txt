cmake_minimum_required(VERSION 3.22)

project(exceptional_control_flow_same_operation)

add_executable(
    ${PROJECT_NAME}
    exceptional_control_flow_same_operation.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
