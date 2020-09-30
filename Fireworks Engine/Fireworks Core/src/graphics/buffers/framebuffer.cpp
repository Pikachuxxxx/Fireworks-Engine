#include "framebuffer.h"
#include <iostream>

fireworks::graphics::FrameBuffer::FrameBuffer(int Width, int Height)
{
	glGenFramebuffers(1, &m_BufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);

	glGenTextures(1, &m_RenderTexture);
	glBindTexture(GL_TEXTURE_2D, m_RenderTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderTexture, 0);

	m_RBO = new RenderBuffer(Width, Height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO->m_BufferID);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete" << std::endl;


 	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

fireworks::graphics::FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_BufferID);
}

void fireworks::graphics::FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
	//glBindTexture(GL_TEXTURE_2D, m_RenderTexture);
}

void fireworks::graphics::FrameBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
