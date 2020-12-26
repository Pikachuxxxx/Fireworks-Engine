#include "buffer.h"


namespace fireworks { namespace graphics {


    Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentCount)
    : m_ComponentCount(componentCount)
    {
        GLCall(glGenBuffers(1, &m_BufferID));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
        GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    Buffer::~Buffer()
    {
        GLCall(glDeleteBuffers(1, &m_BufferID));
    }

    void Buffer::bind() const
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
    }

    void Buffer::unbind() const
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

} }
