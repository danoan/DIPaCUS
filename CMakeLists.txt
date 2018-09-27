cmake_minimum_required(VERSION 3.0)
project(DIPaCUS)

#It expects variables
#CMAKE_PREFIX_PATH: find_[package] macro directories
#CMAKE_INSTALL_PREFIX: install location
#EXTRA_LINK_DIR: extra link directories
#BUILD_PATH: location of build files

link_directories(${EXTRA_LINK_DIR}
        ${BUILD_PATH}/modules/base
        ${BUILD_PATH}/modules/components
        ${BUILD_PATH}/modules/derivates)

set(BUILD_TEST ON CACHE BOOL "Build tests.")


add_subdirectory(modules/base)
add_subdirectory(modules/components)
add_subdirectory(modules/derivates)

if (${BUILD_TEST})
    add_subdirectory(lab/test)
endif ()