cmake_minimum_required(VERSION 3.0)
project(DIPaCUS)

#Global Variables
set(MAGICK++_INCLUDE_DIR /usr/include/GraphicsMagick CACHE PATH "Magick++ include folder.")

set(DIPACUS_BASE_LIB_DIR cmake-build-debug/modules/base CACHE PATH "dipacus-base lib directory.")
set(DIPACUS_COMPONENTS_LIB_DIR cmake-build-debug/modules/components CACHE PATH "dipacus-components lib directory.")
set(DIPACUS_DERIVATES_LIB_DIR cmake-build-debug/modules/derivates CACHE PATH "dipacus-derivates lib directory.")

set(DIPACUS_BUILD_TEST ON CACHE BOOL "Build tests.")


link_directories(${DIPACUS_BASE_LIB_DIR}
        ${DIPACUS_COMPONENTS_LIB_DIR}
        ${DIPACUS_DERIVATES_LIB_DIR})

add_subdirectory(modules/base)
add_subdirectory(modules/components)
add_subdirectory(modules/derivates)
