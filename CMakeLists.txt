cmake_minimum_required(VERSION 3.0)
project(DIPaCUS)

#CMAKE_INSTALL_PREFIX: install location
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


message("Project Root Dir: ${CMAKE_SOURCE_DIR}")
message("Build files at: ${CMAKE_BINARY_DIR}")
message("Installation at: ${CMAKE_INSTALL_PREFIX}")

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )
set(BUILD_TESTS OFF CACHE BOOL "Build tests.")


link_directories(${CMAKE_BINARY_DIR}/modules/base 
        ${CMAKE_BINARY_DIR}/modules/components
        ${CMAKE_BINARY_DIR}/modules/derivates
        ${BOOST_LIBS_DIR})


add_subdirectory(modules/base)
add_subdirectory(modules/components)
add_subdirectory(modules/derivates)

if (${BUILD_TESTS})
    add_subdirectory(lab/test)
endif ()