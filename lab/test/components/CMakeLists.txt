cmake_minimum_required(VERSION 3.2)
project(test-dipacus-components)

find_package(OpenCV  REQUIRED)
find_package(DGtal REQUIRED)

add_executable(test-components
        testComponents.cpp
        src/testMorphology.cpp
        src/data.cpp
        src/testNeighborhood.cpp
        src/testProperties.cpp
        src/testSetOperations.cpp
        src/testTransform.cpp)

add_dependencies(test-components logger dipacus-base dipacus-components dipacus-derivates)

target_compile_definitions(test-components PRIVATE -DPROJECT_DIR=\"${CMAKE_SOURCE_DIR}\")

target_include_directories(test-components PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/base/include
        ${CMAKE_SOURCE_DIR}/modules/components/include
        ${CMAKE_SOURCE_DIR}/modules/derivates/include
        ${CMAKE_SOURCE_DIR}/lab/test/logger/include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(test-components PRIVATE
        -llogger
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})