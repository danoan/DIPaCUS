cmake_minimum_required(VERSION 3.0)
project(DIPaCUS)

#It expects variables CMAKE_PREFIX_PATH EXTRA_LINK_DIR BUILD_PATH

link_directories(${EXTRA_LINK_DIR}
        ${BUILD_PATH}/modules/base
        ${BUILD_PATH}/modules/components
        ${BUILD_PATH}/modules/derivates)


set(DIPACUS_BUILD_TEST ON CACHE BOOL "Build tests.")


add_subdirectory(modules/base)
add_subdirectory(modules/components)
add_subdirectory(modules/derivates)
