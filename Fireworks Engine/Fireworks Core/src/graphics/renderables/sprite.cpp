#include "sprite.h"

namespace fireworks { namespace graphics {


	Sprite::Sprite(maths::vec3 position, maths::vec2 size, maths::vec4 color, Primitive2D primitive2d)
		: Renderable2D(position, size, color, primitive2d), position(m_Position), color(m_Color), m_SpriteSheetDimension(maths::vec2(0, 0)), frame(1), frameRate(0), m_CurrentFrameRate(0), m_AnimTimer(nullptr)
	{

	}

	Sprite::Sprite(maths::vec3 position, maths::vec2 size, Texture* texture, Primitive2D primitive2d)
		: Renderable2D(position, size, maths::vec4(1, 0, 1, 1), primitive2d), position(m_Position), color(m_Color), m_SpriteSheetDimension(maths::vec2(0, 0)), frame(1), frameRate(0), m_CurrentFrameRate(0), m_AnimTimer(nullptr)
	{
		m_Texture = texture;
	}

	Sprite::Sprite(maths::vec3 position, maths::vec2 size, Texture* texture, maths::vec2 sheetDimension, Primitive2D primitive2d)
		: Renderable2D(position, size, maths::vec4(1, 0, 1, 1), primitive2d), position(m_Position), color(m_Color), m_SpriteSheetDimension(sheetDimension), frame(1), frameRate(0), m_CurrentFrameRate(0), m_AnimTimer(new utils::Timer())
	{
		m_Texture = texture;
	}

	Sprite::Sprite(maths::vec3 position, maths::vec2 size, maths::vec4 color, Shader* shader, Primitive2D primitive2d)
        : Renderable2D(position, size, color, primitive2d, shader), position(m_Position), color(m_Color), m_SpriteSheetDimension(maths::vec2(0, 0)), frame(1), frameRate(0), m_CurrentFrameRate(0), m_AnimTimer(nullptr)
    {

    }

    Sprite::Sprite(maths::vec3 position, maths::vec2 size, Shader* shader,Texture* texture, Primitive2D primitive2d)
        : Renderable2D(position, size, maths::vec4(1, 0, 1, 1), primitive2d, shader), position(m_Position), color(m_Color), m_SpriteSheetDimension(maths::vec2(0, 0)), frame(1), frameRate(0), m_CurrentFrameRate(0), m_AnimTimer(nullptr)
    {
        m_Texture = texture;     
	}

	Sprite::Sprite(maths::vec3 position, maths::vec2 size, Shader* shader, Texture* texture, maths::vec2 sheetDimension, Primitive2D primitive2d)
        : Renderable2D(position, size, maths::vec4(1, 0, 1, 1), primitive2d, shader), position(m_Position), color(m_Color), m_SpriteSheetDimension(sheetDimension), frame(1), frameRate(0), m_CurrentFrameRate(0), m_AnimTimer(new utils::Timer())
	{
		m_Texture = texture;
	}

	// TODO: Animate sprites in the actual Engine's time loop automatically
	void Sprite::animateSprite(uint32_t frameRate, SpriteAnimationType animType)
	{
		this->frameRate = frameRate;

		if (animType == SpriteAnimationType::LOOP)
		{
			if (m_CurrentFrameRate > this->frameRate)
			{
				if (this->frame < this->getTotalFrames())
					this->frame += 1;
				else
					this->frame = 1;

				m_CurrentFrameRate = 0.0;
				m_AnimTimer->reset();
			}
			m_CurrentFrameRate += m_AnimTimer->deltaTime();
		}
		else if (animType == SpriteAnimationType::REVERSE)
		{
			if (m_CurrentFrameRate > this->frameRate)
			{
				if (this->frame > 1)
					this->frame -= 1;
				else
					this->frame = this->getTotalFrames();

				m_CurrentFrameRate = 0.0;
				m_AnimTimer->reset();
			}
			m_CurrentFrameRate += m_AnimTimer->deltaTime();
		}
		else if (animType == SpriteAnimationType::PING_PONG)
		{
			static int peakCounter = 0;

			if (m_CurrentFrameRate > this->frameRate)
			{
				if (this->frame < this->getTotalFrames() && peakCounter < this->getTotalFrames())
				{
					this->frame ++;
					peakCounter++;
				}
				else if (peakCounter > this->getTotalFrames())
				{
					this->frame--;
					peakCounter = 0;
				}
				else
				{
					this->frame = 1;
					peakCounter = 0;
				}
				
				m_CurrentFrameRate = 0.0;
				m_AnimTimer->reset();
			}
			m_CurrentFrameRate += m_AnimTimer->deltaTime();
		}
	}

	void Sprite::submit(Renderer2D* renderer) const
	{
		if (m_Texture != nullptr)
			setSpriteSheetUV();
		renderer->submit(this);
	}

	void Sprite::setSpriteSheetUV() const
	{
		if (m_Texture == nullptr)
			return;
		if (frame > getTotalFrames() || frame <= 0)
		{
			// TODO: Log this!
			//std::cerr << "ERROR::SPRITE::Incorrect Frame Index" << std::endl;
			// FIXME: handle the return properly
			frame = 1; // If the user gives the wrong index we display the first frame
			return;
		}
		m_UV.clear();
		float x = (frame - 1) % (int)m_SpriteSheetDimension.x;
		float y = (frame - 1) / (int)m_SpriteSheetDimension.x;
		float frameWidth = m_Texture->getWidth() / m_SpriteSheetDimension.x;
		float frameHeight = m_Texture->getHeight() / m_SpriteSheetDimension.y;
		if (m_Primitive2D == Primitive2D::Quad)
		{
			m_UV.push_back(maths::vec2((x * frameWidth) / m_Texture->getWidth(), (y * frameHeight) / m_Texture->getHeight()));				// Bottom Left
			m_UV.push_back(maths::vec2((x * frameWidth) / m_Texture->getWidth(), ((y + 1) * frameHeight) / m_Texture->getHeight()));		// Top Left
			m_UV.push_back(maths::vec2(((x + 1) * frameWidth) / m_Texture->getWidth(), ((y + 1) * frameHeight) / m_Texture->getHeight()));	// Top Right
			m_UV.push_back(maths::vec2(((x + 1) * frameWidth) / m_Texture->getWidth(), (y * frameHeight) / m_Texture->getHeight()));		// Bottom Right
		}
		else if (m_Primitive2D == Primitive2D::Triangle)
		{
			// TODO: Log this!
			//std::cerr << "ATTENTION::SPRITE:: Triangle primitive does not support spritesheet animation" << std::endl;
			m_UV.push_back(maths::vec2(0, 0));      // Bottom Left
			m_UV.push_back(maths::vec2(0.5, 1));    // Top Middle
			m_UV.push_back(maths::vec2(1, 0));      // Bottom Right
		}
	}
} }
