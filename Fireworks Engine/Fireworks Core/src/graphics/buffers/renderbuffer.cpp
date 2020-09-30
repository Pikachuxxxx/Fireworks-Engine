#include "renderbuffer.h"

fireworks::graphics::RenderBuffer::RenderBuffer(int Width, int Height)
{
	glGenRenderbuffers(1, &m_BufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, m_BufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

fireworks::graphics::RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &m_BufferID);
}

void fireworks::graphics::RenderBuffer::bind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, m_BufferID);
}

void fireworks::graphics::RenderBuffer::unbind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
