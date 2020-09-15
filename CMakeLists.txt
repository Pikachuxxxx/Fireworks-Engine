cmake_minimum_required(VERSION 3.1)

# Project Description
project(Fireworks   VERSION 0.8
                    DESCRIPTION "Sandvox Game Engine"
                    LANGUAGES CXX)
set_target_properties(Fireworks
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/core)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/Fireworks-core/*.c
	${CMAKE_SOURCE_DIR}/Fireworks-core/*.cpp)

# Add source header files
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/Fireworks-core/*.h
	${CMAKE_SOURCE_DIR}/Fireworks-core/*.hpp)

# Configure assets header file
configure_file(${CMAKE_SOURCE_DIR}/Fireworks-core/src/helpers/RootDir.h.in src/helpers/RootDir.h)

# Adding Frameworks
find_package(OpenGL REQUIRED)

# Adding custom libraries
find_library(SOILLIBRARY
    NAMES soil
    HINTS "${CMAKE_SOURCE_DIR}/Dependencies/SOIL/lib"
    )
find_library(GLEW_LIBRARY
    NAMES glew
    HINTS "${CMAKE_SOURCE_DIR}/Dependencies/GLEW/lib"
    )
find_library(GLFW_LIBRARY
    NAMES glfw3
    HINTS "${CMAKE_SOURCE_DIR}/Dependencies/GLFW/lib"
    )
# Adding library include paths
include_directories(
	"${CMAKE_SOURCE_DIR}/Dependencies/SOIL/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/GLEW/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include"
)

set(LIBS ${SOILLIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY} )
set(FRAMEWORKS ${OPENGL_LIBRARIES})
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${FRAMEWORKS} ${LIBS} "-framework CoreFoundation -framework Cocoa -framework IOKit")
