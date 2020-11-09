#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

namespace fireworks { namespace graphics {

	///	Creates Index Buffers.
    class IndexBuffer
    {
    private:
        GLuint m_BufferID;
        GLuint m_Count;
    public:
        /// Generate Index buffer.
        /// 
        /// @param data The index data
        /// @param count Indices count in the index data
        IndexBuffer(GLushort* data, GLsizei count);
        ~IndexBuffer();
        
        /// Bind the index buffer
        void bind() const;
        /// Unbind the index buffer
        void unbind() const;

        /// Gets the indices count
        inline GLuint getCount() const { return m_Count; }
    };

} }
