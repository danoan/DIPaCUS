cmake_minimum_required(VERSION 3.0)
project(test-dipacus-derivates)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(test-derivates testDerivates.cpp src/data.cpp src/testMisc.cpp)

add_dependencies(test-derivates dipacus-base dipacus-components dipacus-derivates logger)

target_compile_definitions(test-derivates PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(test-derivates PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/base/include
        ${CMAKE_SOURCE_DIR}/modules/components/include
        ${CMAKE_SOURCE_DIR}/modules/derivates/include
        ${CMAKE_SOURCE_DIR}/lab/test/logger/include
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-derivates
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -llogger
        -lboost_system
        -lboost_filesystem
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})
