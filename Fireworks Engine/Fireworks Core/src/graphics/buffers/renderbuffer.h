#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

namespace fireworks { namespace graphics {

	class RenderBuffer
	{
	public:
		GLuint m_BufferID;
	public:
		RenderBuffer(int Width, int Height);
		~RenderBuffer();

		void bind() const;
		void unbind() const;
	};
	
} }