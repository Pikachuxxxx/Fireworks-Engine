#pragma once


// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

namespace fireworks { namespace graphics {

	class FrameBuffer
	{
	private:
		GLuint m_BufferID;
	public:
		FrameBuffer();
		~FrameBuffer();

		void bind() const;
		void unbind() const;
	};
} }
