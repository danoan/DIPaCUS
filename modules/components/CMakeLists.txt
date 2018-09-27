cmake_minimum_required(VERSION 3.0)
project(lib-dipacus-components)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

#SHARED LIBRARY
add_library(dipacus-components SHARED
        src/Morphology.cpp
        src/SetOperations.cpp
        src/Transform.cpp
        src/Properties.cpp)

set_target_properties(dipacus-components PROPERTIES
        COMPILE_FEATURES cxx_generic_lambdas
        COMPILE_FLAGS -fext-numeric-literals)

target_include_directories(dipacus-components PRIVATE
        include
        ../base/include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(dipacus-components
        -ldipacus-base
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS dipacus-components
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)


