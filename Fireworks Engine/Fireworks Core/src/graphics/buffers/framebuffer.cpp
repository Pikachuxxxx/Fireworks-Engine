#include "framebuffer.h"
#include <iostream>

fireworks::graphics::FrameBuffer::FrameBuffer(int Width, int Height)
{
	GLCall(glGenFramebuffers(1, &m_BufferID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID));

	GLCall(glGenTextures(1, &m_RenderTexture));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderTexture));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderTexture, 0));

	m_RBO = new RenderBuffer(Width, Height);

	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO->m_BufferID));

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete" << std::endl;


 	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

fireworks::graphics::FrameBuffer::~FrameBuffer()
{
	GLCall(glDeleteFramebuffers(1, &m_BufferID));
}

void fireworks::graphics::FrameBuffer::bind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID));
	//glBindTexture(GL_TEXTURE_2D, m_RenderTexture);
}

void fireworks::graphics::FrameBuffer::unbind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
