cmake_minimum_required(VERSION 3.0)
project(test-dipacus-base)

add_executable(test-base
		testBase.cpp
		src/Representation/testRepresentation.cpp
		src/Representation/data.cpp
		src/Representation/utils/boundingBox.cpp)

add_dependencies(test-base dipacus-base)

set_target_properties(test-base PROPERTIES COMPILE_FEATURES "cxx_generic_lambdas" COMPILE_FLAGS -fext-numeric-literals)

target_compile_definitions(test-base PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(test-base PRIVATE
		include
		${CMAKE_SOURCE_DIR}/modules/base/include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(test-base
        -lboost_system
        -lboost_filesystem
        -ldipacus-base
	${DGTAL_LIBRARIES}
	${OpenCV_LIBS}
)
