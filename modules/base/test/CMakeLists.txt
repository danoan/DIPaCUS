cmake_minimum_required(VERSION 3.0)
project(test-dipacus-base)

add_executable(main main.cpp src/testRepresentation.cpp)

set_target_properties(main PROPERTIES COMPILE_FEATURES "cxx_auto_type;cxx_generic_lambdas;cxx_lambdas")
set_target_properties(main PROPERTIES COMPILE_FLAGS -fext-numeric-literals)

target_compile_definitions(main PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(main PRIVATE
        include
        ../../base/include
        ${MAGICK++_INCLUDE_DIR})

target_link_libraries(main ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS}
        -lboost_system
        -lboost_filesystem
        -ldipacus-base)