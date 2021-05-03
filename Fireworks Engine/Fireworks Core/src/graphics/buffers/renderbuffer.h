#pragma once

// GLEW
#include <GL/glew.h>

#include <src/utils/glassert.h>

namespace fireworks { namespace graphics {

	/// Class to generate Render Buffers.
	class RenderBuffer
	{
	public:
		GLuint m_BufferID;
	public:
		/// Generates the render buffer to store render buffers data.
		RenderBuffer(int Width, int Height);
		~RenderBuffer();

		/// Binds the render buffer
		void bind() const;
		/// Unbinds the render buffer
		void unbind() const;
	};
	
} }