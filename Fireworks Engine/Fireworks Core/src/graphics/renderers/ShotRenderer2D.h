#pragma once

#include "../renderables/renderable2d.h"
#include "renderer2d.h"
#include "../../components/component.h"

namespace fireworks { namespace graphics {

#define SHOT_RENDERER_MAX_SPRITES    1
#define SHOT_RENDERER_VERTEX_SIZE    sizeof(VertexData)
#define SHOT_RENDERER_SPRITE_SIZE    SHOT_RENDERER_VERTEX_SIZE * 4
#define SHOT_RENDERER_BUFFER_SIZE    SHOT_RENDERER_SPRITE_SIZE * SHOT_RENDERER_MAX_SPRITES
#define SHOT_RENDERER_INDICES_SIZE   SHOT_RENDERER_MAX_SPRITES * 6

	/// Renders the renderables on a per draw call basis.
	/// 
	/// Uses one draw call per renderable given to the renderer
	class ShotRenderer2D : public Renderer2D
	{
	private:
		GLuint          m_VAO;
		GLuint          m_VBO;
		VertexData*		m_Buffer;
		IndexBuffer*	m_IBO;
		GLsizei         m_IndicesCount;
		GLuint			m_Texture;
	public:
		/// Creates the renderer from the camera
		/// 
		/// @param The camera to which the renderers output will be displayed to
		ShotRenderer2D(Camera2D* camera);
		~ShotRenderer2D();

		/// Begins the rendering process
		void begin() override;
		/// Begins to submit the renderables to render queue
		void submit(const Renderable2D* renderable) override;
		/// Ends the submission and prepares the renderer to start drawing 
		void end() override;
		/// Draws the data processed onto the screen
		void flush() override;
private:
	void init();

	};

} }