cmake_minimum_required(VERSION 3.10)
project(final_revision)

set(CMAKE_CXX_STANDARD 20)

# Add the project root directory to include paths
include_directories(${PROJECT_SOURCE_DIR})

# Add all source directories
include_directories(
    ${PROJECT_SOURCE_DIR}/Sortings/Comparsion-based-sorting/Quadratic-Sorting-Algorithms
    ${PROJECT_SOURCE_DIR}/Sortings/Comparsion-based-sorting/Sub-quadratic-Sorting-Algorithms
    ${PROJECT_SOURCE_DIR}/RecursionExamples
    ${PROJECT_SOURCE_DIR}/Sortings/Linear-Sorting-Algorithms
    ${PROJECT_SOURCE_DIR}/Sorting/ComplexAlgrothms
    ${PROJECT_SOURCE_DIR}/Liked-Lists/
    ${PROJECT_SOURCE_DIR}/Stacks-and-Queues/Stacks
    ${PROJECT_SOURCE_DIR}/Stacks-and-Queues/Queues
    ${PROJECT_SOURCE_DIR}/tree/AVL/
    ${PROJECT_SOURCE_DIR}/tree/BST/
    ${PROJECT_SOURCE_DIR}/tree/Heap/
)

# Add the main executable
add_executable(final_revision main.cpp)
