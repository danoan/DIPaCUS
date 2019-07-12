cmake_minimum_required(VERSION 3.2)
project(test-dipacus-base)

add_executable(test-base
		testBase.cpp
		src/Representation/testRepresentation.cpp
		src/Representation/data.cpp
		src/Shapes/testShapes.cpp)

add_dependencies(test-base logger dipacus-base)

set_target_properties(test-base PROPERTIES COMPILE_FEATURES "cxx_generic_lambdas" COMPILE_FLAGS -fext-numeric-literals)

target_compile_definitions(test-base PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(test-base PRIVATE
		include
		${CMAKE_SOURCE_DIR}/modules/base/include
		${CMAKE_SOURCE_DIR}/modules/components/include
		${CMAKE_SOURCE_DIR}/lab/test/logger/include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(test-base
		-llogger
		-ldipacus-base
        -lboost_system
        -lboost_filesystem
		${DGTAL_LIBRARIES}
		${OpenCV_LIBS}
)
