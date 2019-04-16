cmake_minimum_required(VERSION 3.2)
project(logger)

find_package(OpenCV  REQUIRED)
find_package(DGtal REQUIRED)

add_library(logger src/logger.cpp)

target_include_directories(logger PRIVATE
        include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(logger
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OPENCV_LIBS})
