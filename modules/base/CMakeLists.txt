cmake_minimum_required(VERSION 3.0)
project(lib-dipacus-base)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_library(dipacus-base STATIC src/Representation.cpp src/Objects.cpp)
target_include_directories(dipacus-base PRIVATE
        include
        ${MAGICK++_INCLUDE_DIR})

target_link_libraries(dipacus-base
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS dipacus-base
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)


if(${DIPACUS_BUILD_TEST})
    add_subdirectory(test)
endif()

