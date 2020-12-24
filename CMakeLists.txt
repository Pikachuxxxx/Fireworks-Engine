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
    ${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Fireworks\ Core/*.cpp)

# Add source header files
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Fireworks\ Core/*.h
    ${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Fireworks\ Core/fireworks.h
    ${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Sandbox/examples/*.h
    ${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Fireworks\ Core/*.hpp)

# External sandbox dependency Files
file(GLOB_RECURSE EXT_SANDBOX_SOURCE_FILES
	${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Sandbox/Test\ Dependencies/*.c
${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Sandbox/Test\ Dependencies/*.cpp)

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
endif(APPLE)
find_library(PNG_LIBRARY
    NAMES png libpng
    HINTS "${CMAKE_SOURCE_DIR}/Dependencies/PNG/lib"
    )
find_library(BZIP2_LIBRARY
    NAMES bzip2
    HINTS "${CMAKE_SOURCE_DIR}/Dependencies/BZIP2/lib"
    )
find_library(FIREWORKS_LIBRARY
   NAMES fireworks
   HINTS "${CMAKE_SOURCE_DIR}/build"
   )
find_library(BOX2D_LIBRARY
   NAMES box2d
   HINTS "${CMAKE_SOURCE_DIR}/Dependencies/Box2D/lib"
   )
find_library(ASSIMP_LIBRARY
   NAMES assimp assimp-vc142-mtd
   HINTS "${CMAKE_SOURCE_DIR}/Dependencies/Box2D/lib"
   )
# Adding library include paths
include_directories(
	"${CMAKE_SOURCE_DIR}/Dependencies/SOIL/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/GLEW/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/FreeType/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/PNG/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/BZIP2"
    "${CMAKE_SOURCE_DIR}/Dependencies/Box2D/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/Assimp/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/OpenAL/include"
    "${CMAKE_SOURCE_DIR}/Fireworks Engine/Sandbox/Test Dependencies"
    "${CMAKE_SOURCE_DIR}/Fireworks Engine/Fireworks Core/"
)

if (APPLE)

# use this for building sandbox
if(BUILD_SANDBOX_EXEC)
set(LIBS ${FIREWORKS_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${FreeType_LIBRARY} ${BOX2D_LIBRARY} ${ASSIMP_LIBRARY})
endif()

set(FRAMEWORKS ${OPENGL_LIBRARIES} ${PNG_LIBRARIES} ${BZIP2_LIBRARIES})

#use this to build the library
if(BUILD_STATIC_LIBRARY)
add_library(fireworks STATIC ${HEADER_FILES} ${SOURCE_FILES} ${EXT_SOURCE_FILES} ${EXT_HEADER_FILES})
endif()

# use hese last 2 commands to run the sandbox
if(BUILD_SANDBOX_EXEC)
add_executable(SandBox ${CMAKE_SOURCE_DIR}/Fireworks\ Engine/Sandbox/Sandbox.cpp ${EXT_SANDBOX_SOURCE_FILES})
target_link_libraries(SandBox ${FRAMEWORKS} ${LIBS} "-framework CoreFoundation -framework CoreAudio -framework OpenAL -framework Cocoa -framework IOKit -framework CoreGraphics")
endif()

endif (APPLE)
