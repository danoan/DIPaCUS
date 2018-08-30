cmake_minimum_required(VERSION 3.0)
project(lib-dipacus-derivates)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_library(dipacus-derivates src/Misc.cpp)

target_include_directories(dipacus-derivates PRIVATE
        include
        ../base/include
        ../components/include
        ${MAGICK++_INCLUDE_DIR}
        )

target_link_libraries(dipacus-derivates
        -ldipacus-base
        -ldipacus-components
        ${DGTAL_LIBRARIES}
        ${OPENCV_LIBRS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS dipacus-derivates
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)


if(${DIPACUS_BUILD_TEST})
    add_subdirectory(test)
endif()