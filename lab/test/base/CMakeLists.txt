cmake_minimum_required(VERSION 3.0)
project(test-dipacus-base)

add_executable(main testBase.cpp src/testRepresentation.cpp)

set_target_properties(main PROPERTIES COMPILE_FEATURES "cxx_generic_lambdas" COMPILE_FLAGS -fext-numeric-literals)

target_compile_definitions(main PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(main PRIVATE
		include
		../../../modules/base/include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(main
        -lboost_system
        -lboost_filesystem
        -ldipacus-base
	${DGTAL_LIBRARIES}
	${OpenCV_LIBS}
)
