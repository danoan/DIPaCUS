cmake_minimum_required(VERSION 3.2)
project(lib-dipacus-components)


#SHARED LIBRARY
add_library(dipacus-components SHARED
        src/Morphology.cpp
        src/Neighborhood.cpp
        src/SetOperations.cpp
        src/Transform.cpp
        src/Properties.cpp
        src/properties/boundingBox.cpp)

add_dependencies(dipacus-components dipacus-base)

set_target_properties(dipacus-components PROPERTIES
        COMPILE_FEATURES cxx_generic_lambdas
        COMPILE_FLAGS -fext-numeric-literals)

target_include_directories(dipacus-components PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/base/include
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(dipacus-components
        -ldipacus-base
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS dipacus-components
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
