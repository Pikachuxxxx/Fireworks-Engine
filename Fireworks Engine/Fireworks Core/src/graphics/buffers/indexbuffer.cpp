#include "indexbuffer.h"

namespace fireworks { namespace graphics {


    IndexBuffer::IndexBuffer(GLushort* data, GLsizei count)
    : m_Count(count)
    {
        // TODO!: Fix unexpected crashing (suspected reason: improper dereferencing of IndexBuffer pointer(s))
        GLCall(glGenBuffers(1, &m_BufferID));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_DYNAMIC_DRAW));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    IndexBuffer::~IndexBuffer()
    {
        GLCall(glDeleteBuffers(1, &m_BufferID));
    }

    void IndexBuffer::bind() const
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
    }

    void IndexBuffer::unbind() const
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

} }
