cmake_minimum_required(VERSION 3.0)
project(test-dipacus-derivates)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(testDerivates testDerivates.cpp src/testComputeBoundaryCurve.cpp src/testCompactSetFromClosedCurve.cpp)

add_dependencies(testDerivates dipacus-derivates)

target_compile_definitions(testDerivates PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(testDerivates PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/derivates/include
        ${CMAKE_SOURCE_DIR}/modules/base/include
        ${CMAKE_SOURCE_DIR}/modules/components/include
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(testDerivates
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_system
        -lboost_filesystem
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})
