cmake_minimum_required(VERSION 3.10)

project(adding_context_with_cout)

add_executable(
    ${PROJECT_NAME}
    adding_context_with_cout.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
