cmake_minimum_required(VERSION 3.1)

# Project Description
project(Fireworks   VERSION 1.0
                    DESCRIPTION "Sandbox Game Engine"
                    )

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/Fireworks-core/*.c
	${CMAKE_SOURCE_DIR}/Fireworks-core/*.cpp)

# Add source header files
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/Fireworks-core/*.h
	${CMAKE_SOURCE_DIR}/Fireworks-core/*.hpp)

# Add external header files
file(GLOB_RECURSE EXT_HEADER_FILES
	${CMAKE_SOURCE_DIR}/Fireworks-core/ext/*.h
	${CMAKE_SOURCE_DIR}/Fireworks-core/*.hpp)

# Configure assets header file
configure_file(${CMAKE_SOURCE_DIR}/Fireworks-core/src/helpers/RootDir.h.in src/helpers/RootDir.h)

# Adding Frameworks
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)
find_package(BZip2 REQUIRED)

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
find_library(FreeType_LIBRARY
    NAMES freetype
    HINTS "${CMAKE_SOURCE_DIR}/Dependencies/FreeType/lib"
    )
find_library(FTGL_LIBRARY
    NAMES ftgl
    HINTS "${CMAKE_SOURCE_DIR}/Dependencies/FTGL/lib"
    )
find_library(FIREWORKS_LIBRARY
    NAMES fireworks
    HINTS "${CMAKE_SOURCE_DIR}/build"
    )
# Adding library include paths
include_directories(
	"${CMAKE_SOURCE_DIR}/Dependencies/SOIL/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/GLEW/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/FreeType/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/FTGL/include"
    "${CMAKE_SOURCE_DIR}/build/include"
)

set(LIBS ${SOILLIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${FIREWORKS_LIBRARY})
set(FRAMEWORKS ${OPENGL_LIBRARIES} ${FreeType_LIBRARY} ${FTGL_LIBRARY} ${PNG_LIBRARIES} ${ZLIB_LIBRARIES} ${BZIP2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${FRAMEWORKS} ${LIBS} "-framework CoreFoundation -framework Cocoa -framework IOKit -framework CoreGraphics")
# add_library(fireworks STATIC ${HEADER_FILES} ${SOURCE_FILES} ${EXT_SOURCE_FILES} ${EXT_HEADER_FILES})
