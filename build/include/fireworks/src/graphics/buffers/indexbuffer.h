#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

namespace fireworks { namespace graphics {

    class IndexBuffer
    {
    private:
        GLuint m_BufferID;
        GLuint m_Count;
    public:
        IndexBuffer(GLushort* data, GLsizei count);
        ~IndexBuffer();
        
        void bind() const;
        void unbind() const;

        inline GLuint getCount() const { return m_Count; }
    };

} }
