cmake_minimum_required(VERSION 3.2)
project(lib-dipacus-derivates)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(dipacus-derivates ${LIBRARY_ACTION} src/Misc.cpp)

add_dependencies(dipacus-derivates dipacus-base dipacus-components)

target_include_directories(dipacus-derivates PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/base/include
        ${CMAKE_SOURCE_DIR}/modules/components/include
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS}
        )

target_link_libraries(dipacus-derivates
        -ldipacus-base
        -ldipacus-components
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

set_target_properties(dipacus-derivates PROPERTIES
        COMPILE_FEATURES cxx_generic_lambdas
        COMPILE_FLAGS -fext-numeric-literals
        VERSION ${VERSION_DIPACUS_DERIVATES})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS dipacus-derivates
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)


