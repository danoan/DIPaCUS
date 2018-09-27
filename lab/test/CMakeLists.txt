cmake_minimum_required(VERSION 3.2)
project(dipacus-test)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_subdirectory(base)
add_subdirectory(derivates)