cmake_minimum_required(VERSION 3.10)

project(checking_with_return_enum)

add_executable(
    ${PROJECT_NAME}
    checking_with_return_enum.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
