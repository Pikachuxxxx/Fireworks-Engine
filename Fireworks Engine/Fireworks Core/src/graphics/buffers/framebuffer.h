#pragma once


// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include "renderbuffer.h"

namespace fireworks { namespace graphics {

	class FrameBuffer
	{
	private:
		GLuint		   m_BufferID;
		GLuint		   m_RenderTexture;
		RenderBuffer*  m_RBO;
	public:
		FrameBuffer(int Width, int Height);
		~FrameBuffer();

		void bind() const;
		void unbind() const;

		inline GLuint getRenderTexture() const { return m_RenderTexture;  }
	};
} }
