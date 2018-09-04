cmake_minimum_required(VERSION 3.0)
project(lib-dipacus-base)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

#STATIC LIBRARY
add_library(dipacus-base-st STATIC src/Representation.cpp src/Objects.cpp)

target_include_directories(dipacus-base-st PRIVATE
        include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(dipacus-base-st
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

set_target_properties(dipacus-base-st
        PROPERTIES
        COMPILE_FEATURES "cxx_generic_lambdas"
        COMPILE_FLAGS -fext-numeric-literals
        )


#SHARED LIBRARY
add_library(dipacus-base SHARED src/Representation.cpp src/Objects.cpp)

target_include_directories(dipacus-base PRIVATE
        include
        ${DGTAL_INCLUDE_DIRS})

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

install(TARGETS dipacus-base-st dipacus-base
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)


if(${DIPACUS_BUILD_TEST})
    add_subdirectory(test)
endif()

