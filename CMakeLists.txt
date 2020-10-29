cmake_minimum_required(VERSION 3.1)

# Project Description
project(Fireworks   VERSION 1.0
                    DESCRIPTION "Fireworks Engine"
                    )
# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Fireworks\ Core/*.c
    ${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Sandbox/Sandbox.cpp
    ${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Fireworks\ Core/*.cpp)

# Add source header files
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Fireworks\ Core/*.h
    ${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Fireworks\ Core/fireworks.h
    ${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Sandbox/examples/*.h
    ${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Fireworks\ Core/*.hpp)

# Add external header files
file(GLOB_RECURSE EXT_HEADER_FILES
	${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Fireworks\ Core/ext/*.h
    ${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Fireworks\ Core/*.hpp
    ${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Fireworks\ Core/vendor/*.h
    ${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Fireworks\ Core/vendor/*.hpp)


# Adding Frameworks
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)
find_package(BZip2 REQUIRED)

# Adding custom libraries
find_library(GLEW_LIBRARY
    NAMES glew libglew glew32s
    HINTS "${CMAKE_SOURCE_DIR}/Dependencies/GLEW/lib"
    )
find_library(GLFW_LIBRARY
    NAMES glfw3 libglfw3
    HINTS "${CMAKE_SOURCE_DIR}/Dependencies/GLFW/lib"
    )
if(APPLE)
find_library(FreeType_LIBRARY
    NAMES freetype libfreetype
    HINTS "${CMAKE_SOURCE_DIR}/Dependencies/FreeType/lib"
    )
# find_library(FTGL_LIBRARY
#     NAMES ftgl libftgl
#     HINTS "${CMAKE_SOURCE_DIR}/Dependencies/FTGL/lib"
#     )
endif(APPLE)
find_library(PNG_LIBRARY
    NAMES png libpng
    HINTS "${CMAKE_SOURCE_DIR}/Dependencies/PNG/lib"
    )
find_library(BZIP2_LIBRARY
    NAMES bzip2
    HINTS "${CMAKE_SOURCE_DIR}/Dependencies/BZIP2/lib"
    )
# Check the library name and directory based on OS
find_library(OpenAL_LIBRARY
    NAMES OpenAL OpenAL32
    HINTS "${CMAKE_SOURCE_DIR}/Dependencies/OpenAL/lib"
    HINTS "${CMAKE_SOURCE_DIR}/Dependencies/OpenAL/Win64/lib"
    )
#find_library(FIREWORKS_LIBRARY
#    NAMES fireworks
#    HINTS "${CMAKE_SOURCE_DIR}/build"
#    )
# Adding library include paths
include_directories(
	"${CMAKE_SOURCE_DIR}/Dependencies/SOIL/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/GLEW/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/FreeType/include"
    # "${CMAKE_SOURCE_DIR}/Dependencies/FTGL/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/PNG/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/BZIP2"
    "${CMAKE_SOURCE_DIR}/Dependencies/OpenAL/include"
    "${CMAKE_SOURCE_DIR}/Fireworks Engine/Sandbox/Test Dependencies"
    "${CMAKE_SOURCE_DIR}/Fireworks Engine/Fireworks Core/"
#   "${CMAKE_SOURCE_DIR}/build/include"
)

if (WIN32)
    set(LIBS ${SOIL_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${PNG_LIBRARY} ${BZIP2_LIBRARY})
endif (WIN32)
if (APPLE)
    set(LIBS ${SOIL_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${FreeType_LIBRARY} ${FTGL_LIBRARY})
endif (APPLE)

set(FRAMEWORKS ${OPENGL_LIBRARIES} ${PNG_LIBRARIES} ${BZIP2_LIBRARIES})
# add_library(fireworks STATIC ${FRAMEWORKS} ${LIBS} ${HEADER_FILES} ${SOURCE_FILES} ${EXT_SOURCE_FILES} ${EXT_HEADER_FILES})
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${EXT_SOURCE_FILES} ${EXT_HEADER_FILES})
if (WIN32)
    target_link_libraries(${PROJECT_NAME} ${FRAMEWORKS} ${LIBS})
endif (WIN32)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} ${FRAMEWORKS} ${LIBS} "-framework CoreFoundation -framework CoreAudio -framework OpenAL -framework Cocoa -framework IOKit -framework CoreGraphics")
endif (APPLE)
