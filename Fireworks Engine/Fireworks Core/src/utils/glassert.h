#pragma once

#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

namespace fireworks {

    //#ifdef ((_WIN32) || (_WIN64)) // This OS Macro isn't working why?
    #define ASSERT(x) if (!(x)) __debugbreak(); // Break the debugger from executing 
    #define GLCall(x)   GLClearError();\
                        (x);\
                        ASSERT(GLLogCall(#x, __FILE__, __LINE__))
    //#endif
            
    static void GLClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    static bool GLLogCall(const char* functionName, const char* file, int line)
    {
        while (GLenum error = glGetError())
        {
            std::cerr << "OpenGL::ERROR:: " << error << "[Function : " << functionName << ", File : " << file << ", at Line : " << line << "]" << std::endl;
            return false;
        }
        return true;
    }
}