cmake_minimum_required(VERSION 3.2)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "DIPaCUS binaries and libraries install location." )
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}")

set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )
set(BUILD_TESTS OFF CACHE BOOL "Build tests.")
set(CREATE_SHARED_LIBRARIES ON CACHE BOOL "Create shared libraries. If off, create static libraries.")

project(DIPaCUS)


message("Project Root Dir: ${CMAKE_SOURCE_DIR}")
message("Build files at: ${CMAKE_BINARY_DIR}")
message("Installation at: ${CMAKE_INSTALL_PREFIX}")

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)


link_directories(${CMAKE_BINARY_DIR}/modules/base 
        ${CMAKE_BINARY_DIR}/modules/components
        ${CMAKE_BINARY_DIR}/modules/derivates
	${CMAKE_BINARY_DIR}/lab/test/logger
        ${BOOST_LIBS_DIR})


add_subdirectory(modules/base)
add_subdirectory(modules/components)
add_subdirectory(modules/derivates)

if (${BUILD_TESTS})
    add_subdirectory(lab/test)
endif ()
