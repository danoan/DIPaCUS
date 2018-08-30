cmake_minimum_required(VERSION 3.0)
project(lib-dipacus-components)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_library(dipacus-components STATIC
        src/Morphology.cpp
        src/SetOperations.cpp
        src/Transform.cpp)

set_target_properties(dipacus-components PROPERTIES
        COMPILE_FEATURES "cxx_auto_type;cxx_lambdas;cxx_generic_lambdas"
        COMPILE_FLAGS -fext-numeric-literals)

target_include_directories(dipacus-components PRIVATE
        include
        ../base/include
        ${MAGICK++_INCLUDE_DIR})

target_link_libraries(dipacus-components
        -lbase
        ${DGTAL_LIBRARIES}
        ${OPENCV_LIBRS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS dipacus-components
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

if(${DIPACUS_BUILD_TEST})
    add_subdirectory(test)
endif()


