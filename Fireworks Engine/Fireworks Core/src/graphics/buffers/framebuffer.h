#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include "renderbuffer.h"

#include "../../utils/glassert.h"

namespace fireworks { namespace graphics {

	/// Class to generate Frame Buffers.
	class FrameBuffer
	{
	private:
		GLuint		   m_BufferID;
		GLuint		   m_RenderTexture;
		RenderBuffer*  m_RBO;
	public:
		/// Generates frame buffers to render the current scene to the generated frame buffer.
		/// 
		/// @param Width The Width of the render texture that the frame will be mapped to.
		/// @param Height The Height of the render texture that the frame will be mapped to.
		FrameBuffer(int Width, int Height);
		~FrameBuffer();

		/// Bind the frame buffer 
		void bind() const;
		/// Unbind the frame buffer
		void unbind() const;

		/// Gets the Render Texture that the current frame was mapped to
		inline GLuint getRenderTexture() const { return m_RenderTexture;  }
	};
} }
