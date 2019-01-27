cmake_minimum_required(VERSION 3.2)
project(test-dipacus-utils)

find_package(OpenCV REQUIRED)
find_package(DGtal REQUIRED)

add_library(test-dipacus-utils SHARED
        src/utils.cpp
        src/boundingBox.cpp)

add_dependencies(test-dipacus-utils dipacus-base dipacus-components dipacus-derivates)

target_include_directories(test-dipacus-utils PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/base/include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(test-dipacus-utils
        -ldipacus-base
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})
