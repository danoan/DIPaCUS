cmake_minimum_required(VERSION 3.0)
project(lib-dipacus-derivates)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)


#SHARED LIBRARY
add_library(dipacus-derivates SHARED src/Misc.cpp)

add_dependencies(dipacus-derivates dipacus-base dipacus-components)

target_include_directories(dipacus-derivates PRIVATE
        include
        ../base/include
        ../components/include
        ${DGTAL_INCLUDE_DIRS}
        )

target_link_libraries(dipacus-derivates
        -ldipacus-base
        -ldipacus-components
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

set_target_properties(dipacus-derivates PROPERTIES
        COMPILE_FEATURES cxx_generic_lambdas
        COMPILE_FLAGS -fext-numeric-literals)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS dipacus-derivates
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)


