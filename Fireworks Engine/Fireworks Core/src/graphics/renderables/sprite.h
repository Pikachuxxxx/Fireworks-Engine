#pragma once

#include "renderable2d.h"
#include "../../utils/timer.h"

namespace fireworks { namespace graphics {

    /// The type of sprite sheet animation.
    enum class SpriteAnimationType
    {
        LOOP,
        REVERSE,
        PING_PONG
    };

    /// The class responsible for drawing the Sprites in the scene.
    class Sprite : public Renderable2D
    {
    public:
        /// The frame number in the sprite sheet. 
        /// 
        /// @note We use Row major way conversion of 2D sheet into 1D
mutable std::uint32_t       frame;
        /// The rate at which the frames are displayed.
        /// 
        /// @note low frameRate means frames change faster
        std::uint32_t       frameRate;
        /// The position of the Sprite.
		maths::vec3&        position;
        /// The color of the Sprite.
		maths::vec4&        color;
        /// The size of the Sprite.
        maths::vec2&        size;
        /// The rotation of the Sprite.
        float&              rotation;
	private:
		maths::vec2         m_SpriteSheetDimension;
		utils::Timer*       m_AnimTimer;
        double              m_CurrentFrameRate;
    public:
        /// Create and empty sprite with this constructor.
        Sprite();
        // To use with BatchRenderer
        /// Create Sprite renderable.
        /// 
        /// @param position The position at which the sprite should be rendered at
        /// @param size The dimensions of the sprite
        /// @parma color The color of the sprite
        /// @param primitive2d The primitive shape with which the Sprite should be rendered with
        /// @warning This overload is to be used with the graphics::BatchRenderer2D because it doesn't not accept any shader
        Sprite(maths::vec3 position, maths::vec2 size, maths::vec4 color, Primitive2D primitive2d = Primitive2D::Quad);
		/// Create Sprite renderable.
        /// 
        /// @param position The position at which the sprite should be rendered at
        /// @param size The dimensions of the sprite
        /// @parma texture The Texture with which the sprite should be rendered with
        /// @param primitive2d The primitive shape with which the Sprite should be rendered with
        /// @warning This overload is to be used with the graphics::BatchRenderer2D because it doesn't not accept any shader
        /// @see Texture for more information on how to Textures
		Sprite(maths::vec3 position, maths::vec2 size, Texture* texture, Primitive2D primitive2d = Primitive2D::Quad);
		/// Create Sprite renderable.
        /// 
        /// @param position The position at which the sprite should be rendered at
        /// @param size The dimensions of the sprite
        /// @parma texture The Texture with which the sprite should be rendered with
        /// @param sheetDimension The dimensions of the sprite sheet i.e. no of sprites in the sheet not the actual dimensions of the sheet
        /// @param primitive2d The primitive shape with which the Sprite should be rendered with
        /// @attention sheetDimension requires the the number of sprites in the (row, column) count maths::vec2 and not that actual dimensions of the sheet itself
        /// @warning This overload is to be used with the graphics::BatchRenderer2D because it doesn't not accept any shader
        /// @see Texture for more information on how to Textures
		Sprite(maths::vec3 position, maths::vec2 size, Texture* texture, maths::vec2 sheetDimension, Primitive2D primitive2d = Primitive2D::Quad);

        // To use with a SimpleRenderer aka Instance Renderer
		/// Create Sprite renderable.
		/// 
		/// @param position The position at which the sprite should be rendered at
		/// @param size The dimensions of the sprite
		/// @parma color The color of the sprite
        /// @param shader The shader with which you want the sprite to be rendered with
		/// @param primitive2d The primitive shape with which the Sprite should be rendered with
		/// @warning This overload is to be used with the graphics::InstanceRenderer2D if you want the shader to be used
		Sprite(maths::vec3 position, maths::vec2 size, maths::vec4 color, Shader* shader, Primitive2D primitive2d = Primitive2D::Quad);
		/// Create Sprite renderable.
        /// 
        /// @param position The position at which the sprite should be rendered at
        /// @param size The dimensions of the sprite
        /// @parma color The color of the sprite
        /// @param shader The shader with which you want the sprite to be rendered with
        /// @parma texture The Texture with which the sprite should be rendered with
        /// @param primitive2d The primitive shape with which the Sprite should be rendered with
        /// @warning This overload is to be used with the graphics::InstanceRenderer2D if you want the shader to be used
		Sprite(maths::vec3 position, maths::vec2 size, Shader* shader,Texture* texture, Primitive2D primitive2d = Primitive2D::Quad);\
		/// Create Sprite renderable.
        /// 
        /// @param position The position at which the sprite should be rendered at
        /// @param size The dimensions of the sprite
        /// @parma color The color of the sprite
        /// @param shader The shader with which you want the sprite to be rendered with
        /// @parma texture The Texture with which the sprite should be rendered with
        /// @param sheetDimension The dimensions of the sprite sheet i.e. no of sprites in the sheet not the actual dimensions of the sheet
        /// @param primitive2d The primitive shape with which the Sprite should be rendered with
        /// @attention sheetDimension requires the the number of sprites in the (row, column) count maths::vec2 and not that actual dimensions of the sheet itself
        /// @warning This overload is to be used with the graphics::InstanceRenderer2D if you want the shader to be used
		Sprite(maths::vec3 position, maths::vec2 size, Shader* shader, Texture* texture, maths::vec2 sheetDimension, Primitive2D primitive2d = Primitive2D::Quad);

        /// The overridden callback function that confirms the addition of physics:;RigidBody2D component to the Sprite
		void addedRigidBody2D() override;

        /// Animate the sprite by setting the framerate and the type of animation style
        /// 
        /// @param frameRate The frame rate at which you want the animation to play
        /// @param animType The type of animation 
        /// @see See graphics::SpriteAnimationType for more information
        void animateSprite(uint32_t frameRate, SpriteAnimationType animType);

        /// Gets the total frames in the sprite sheet
		inline const uint32_t getTotalFrames() const { return (m_SpriteSheetDimension.x * m_SpriteSheetDimension.y); }
    private:    
        void submit(Renderer2D* renderer) const override;
        void setSpriteSheetUV() const;
    };
} }
