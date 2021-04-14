#pragma once

// GLEW
#include <GL/glew.h>

#include <src/utils/glassert.h>

namespace fireworks { namespace graphics {

	/// Creates Vertex Buffers.
	class Buffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_ComponentCount;
	public:
		/// Create and generate VertexBuffer.
		/// 
		/// @param data The vertex data of the geometry
		/// @param count The count of the number of variants of vertex data 
		/// @param componentCount The count of different variations of vertex data
		Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
		~Buffer();

		/// Bind the buffer
		void bind() const;
		/// Unbind the buffer
		void unbind() const;

		/// Gets the types of components in the vertex data.
		inline GLuint getComponentCount() const { return m_ComponentCount; }
	};
} }
