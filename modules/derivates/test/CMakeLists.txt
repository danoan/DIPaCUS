cmake_minimum_required(VERSION 3.0)
project(test-dipacus-derivates)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(testDerivates testDerivates.cpp src/testComputeBoundaryCurve.cpp src/testCompactSetFromClosedCurve.cpp)

target_compile_definitions(testDerivates PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(testDerivates PRIVATE
        ${DGTAL_INCLUDE_DIRS}
        include
        ../include
        ../../base/include
        ../../components/include)

target_link_libraries(testDerivates
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_system
        -lboost_filesystem
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})
