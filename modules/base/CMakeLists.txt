cmake_minimum_required(VERSION 3.2)
project(lib-dipacus-base)

#SHARED LIBRARY
add_library(dipacus-base SHARED src/Representation.cpp src/Objects.cpp)

target_include_directories(dipacus-base PRIVATE
        include
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(dipacus-base
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

set_target_properties(dipacus-base
        PROPERTIES
        COMPILE_FEATURES "cxx_generic_lambdas"
        COMPILE_FLAGS -fext-numeric-literals
        )

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS dipacus-base
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)


