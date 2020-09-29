#include "framebuffer.h"

fireworks::graphics::FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &m_BufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
}

fireworks::graphics::FrameBuffer::~FrameBuffer()
{

}

void fireworks::graphics::FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
}

void fireworks::graphics::FrameBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
