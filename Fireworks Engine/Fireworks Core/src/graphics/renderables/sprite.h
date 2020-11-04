#pragma once

#include "renderable2d.h"
#include "../../utils/timer.h"

namespace fireworks { namespace graphics {

    enum class SpriteAnimationType
    {
        LOOP,
        REVERSE,
        PING_PONG
    };
    class Sprite : public Renderable2D
    {
    public:
mutable std::uint32_t       frame;
        std::uint32_t       frameRate;
		maths::vec3&        position;
		maths::vec4&        color;
        maths::vec2&        size;
	private:
		maths::vec2         m_SpriteSheetDimension;
		utils::Timer*       m_AnimTimer;
        double              m_CurrentFrameRate;
    public:
        Sprite();
        // To use with BatchRenderer
        Sprite(maths::vec3 position, maths::vec2 size, maths::vec4 color, Primitive2D primitive2d = Primitive2D::Quad);
		Sprite(maths::vec3 position, maths::vec2 size, Texture* texture, Primitive2D primitive2d = Primitive2D::Quad);
		Sprite(maths::vec3 position, maths::vec2 size, Texture* texture, maths::vec2 sheetDimension, Primitive2D primitive2d = Primitive2D::Quad);

        // To use with a SimpleRenderer aka Instance Renderer
		Sprite(maths::vec3 position, maths::vec2 size, maths::vec4 color, Shader* shader, Primitive2D primitive2d = Primitive2D::Quad);
		Sprite(maths::vec3 position, maths::vec2 size, Shader* shader,Texture* texture, Primitive2D primitive2d = Primitive2D::Quad);
		Sprite(maths::vec3 position, maths::vec2 size, Shader* shader, Texture* texture, maths::vec2 sheetDimension, Primitive2D primitive2d = Primitive2D::Quad);

		void addedRigidBody2D() override;

        void animateSprite(uint32_t frameRate, SpriteAnimationType animType);

		inline const uint32_t getTotalFrames() const { return (m_SpriteSheetDimension.x * m_SpriteSheetDimension.y); }
    private:    
        void submit(Renderer2D* renderer) const override;
        void setSpriteSheetUV() const;
    };
} }
