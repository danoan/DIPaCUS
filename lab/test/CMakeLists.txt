cmake_minimum_required(VERSION 3.2)
project(dipacus-test)

link_directories(${CMAKE_SOURCE_DIR}/cmake-build-debug/lab/test/logger)

add_subdirectory(logger)

add_subdirectory(base)
add_subdirectory(components)
add_subdirectory(derivates)