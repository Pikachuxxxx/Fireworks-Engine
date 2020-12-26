#include "renderbuffer.h"

fireworks::graphics::RenderBuffer::RenderBuffer(int Width, int Height)
{
	GLCall(glGenRenderbuffers(1, &m_BufferID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_BufferID));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

fireworks::graphics::RenderBuffer::~RenderBuffer()
{
	GLCall(glDeleteRenderbuffers(1, &m_BufferID));
}

void fireworks::graphics::RenderBuffer::bind() const
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_BufferID));
}

void fireworks::graphics::RenderBuffer::unbind() const
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}
