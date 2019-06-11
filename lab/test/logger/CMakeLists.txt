cmake_minimum_required(VERSION 3.2)
project(logger)

find_package(OpenCV  REQUIRED)
find_package(DGtal REQUIRED)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(logger ${LIBRARY_ACTION}
        src/logger.cpp )

target_include_directories(logger PRIVATE
        include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(logger
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OPENCV_LIBS})
