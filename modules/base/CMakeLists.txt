cmake_minimum_required(VERSION 3.2)
project(lib-dipacus-base)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()


add_library(dipacus-base ${LIBRARY_ACTION}
        src/Representation.cpp
        src/Shapes.cpp
        src/shapes/WaveShape.cpp)

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
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)



