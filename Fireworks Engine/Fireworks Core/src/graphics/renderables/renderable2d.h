#pragma once

#include <vector>
#include <iostream>

#include "../shader.h"
#include "../buffers/buffer.h"
#include "../buffers/indexbuffer.h"
#include "../buffers/vertexarray.h"
#include "../../maths/maths.h"
#include "../renderers/renderer2d.h"
#include "../texture.h"
#include "../../physics/rigidbody2d.h"

namespace fireworks { namespace graphics {

    /// The structure of the Vertex Data
    struct VertexData
    {
        maths::vec3 vertex;
        maths::vec2 uv;
        float       tid;
        maths::vec4 color;
    };

    /// Different variations of primitives
    enum class Primitive2D
    {
        Circle,
        Triangle,
        Quad
    };

    /// The Class responsible for drawing the basic Renderable objects onto the screen.
    /// 
    /// Every renderable type is derived from this class
    class Renderable2D
    {
    public:
        /// The unique ID of the renderable object
        std::uint32_t                       objectID;
        /// The Shader used to draw the particular renderable
        /// 
        /// @note This shader is used only when using the graphics::InstanceRenderer2D Renderer, unlike for the graphics::BatchRenderer2D which used a global shader for all the renderables
        Shader*                             shader;
        /// tells whether or not the renderable is flipped on the X-axis or not
		bool                                flippedX;
        /// tells whether or not the renderable is flipped on the Y-axis or not
        bool                                flippedY;
        /// The collection of Components that is attached to the renderable
        std::vector<components::Component*> components;
    protected:
        /// The size of the renderable
		maths::vec2                         m_Size;
        /// The position of the renderable 
		maths::vec3                         m_Position;
        /// The color of the renderable
		maths::vec4                         m_Color;
        /// The rotation of the renderable along the Z-Axis
        float                               m_Rotation;
        /// The primitive that is used to draw the renderable
        Primitive2D                         m_Primitive2D;
        /// The UV coordinates of the renderable
mutable std::vector<maths::vec2>            m_UV;
        /// The texture (if any) used by the renderable
		Texture*                            m_Texture;
    private:
 static std::uint32_t                       m_UniqueID;
    public:
        /// Creates the renderable. 
        /// 
        /// @param position The position of the renderable
        /// @param size The Size of the renderable
        /// @param color The color of the renderable
        /// @primiitve2d The primitive shape of the renderable (Quad or Triangle)
        /// @note This overload is to be used with graphics::BatchRenderer2D
		Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color, Primitive2D primitive2d)
			: m_Position(position), m_Size(size), m_Color(color), m_Primitive2D(primitive2d), shader(nullptr), m_Texture(nullptr), m_Rotation(0.0f)
		{
            objectID = ++m_UniqueID;
			setUVDefaults();
		}

		/// Creates the renderable. 
		/// 
		/// @param position The position of the renderable
		/// @param size The Size of the renderable
		/// @param color The color of the renderable
		/// @primiitve2d The primitive shape of the renderable (Quad or Triangle)
        /// @param shader The shader with which the renderable is to be rendered with
		/// @note This overload is to be used with graphics::BatchRenderer2D
        Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color, Primitive2D primitive2d, Shader* shader)
            : m_Position(position), m_Size(size), m_Color(color), m_Primitive2D(primitive2d), shader(shader), m_Texture(nullptr), m_Rotation(0.0f)
        { 
			objectID = ++m_UniqueID;
			shader->enable();
			GLint texIDs[] =
			{
				0, 1,  2,  3,  4,  5,  6,  7,
				8, 9, 10, 11, 12, 13, 14, 15
			};
			shader->setUniform1iv("textures", texIDs, 8);
			shader->disable();

            setUVDefaults();
        }

        virtual ~Renderable2D() { }

        /// Virtual overload of the submit function, customize the way you can submit the renderable to the renderer
        virtual void submit(Renderer2D* renderer) const
        {
            renderer->submit(this);
        }

        /// Template methods of various ways of adding components to the renderable
        /// 
        /// @param component The component to add to the renderable
		template <typename T>
		void AddComponent(components::Component* component)
		{
			components.push_back(component);

			if ((dynamic_cast<physics::RigidBody2D*>(component)))
				std::cout << "Added a rigibody2d component" << std::endl;
		}

        /// The Rigidbody2D overload template
		template <>
		void AddComponent<physics::RigidBody2D>(components::Component* component)
		{
			components.push_back(component);
			//if ((dynamic_cast<physics::RigidBody2D*>(component)))
				std::cout << "Added a rigibody2d component in the rigidBody overload" << std::endl;

			this->addedRigidBody2D();
		}

        /// Gets the position of the Renderable.
        /// 
        /// Checks the components and returns the proper position after making necessary calculations and conditional analysis
        inline const maths::vec3& getPosition() const { const_cast<Renderable2D*>(this)->GetRigidBody2DPosition();  return m_Position; }
		/// Gets the rotation of the Renderable.
        /// 
        /// Checks the components and returns the proper rotation after making necessary calculations and conditional analysis
		inline const float& getRotation() const { const_cast<Renderable2D*>(this)->GetRigidBody2DRotation();  return m_Rotation; }
        /// Gets the size of the renderable.
        inline const maths::vec2& getSize() const { return m_Size; }
        /// Gets the color of the renderable.
        inline const maths::vec4& getColor() const { return m_Color; }
        /// Gets the primitive shape that is used to draw the renderable.
		inline const Primitive2D getPrimitive() const { return m_Primitive2D; }
        /// Gets the UV coordinates of the 2D Renderable.
        inline const std::vector<maths::vec2>& getUV() const { return m_UV; }
        /// Gets the texture that is used to draw the renderable.
        inline const Texture* getTexture() const { return m_Texture; }
        /// Gets the ID of the renderables texture.
        inline const GLuint getTID() const { return m_Texture == nullptr ? 0 : m_Texture->getID(); }
        
        // Custom Methods
        /// Flip the Renderable along the X-axis.
        void flipX() { flippedX = true; }
        /// Unflip the Renderable along the X-axis.
        void unflipX() { flippedX = false; }
        /// Flip the Renderable along the Y-axis.
        void flipY() { flippedY = true; }
        /// Unflip the Renderable along the X-axis.
        void unflipY() { flippedY = false; }

	protected:
        /// Create an empty renderable
		Renderable2D() : m_Texture(nullptr)
        {
			objectID = ++m_UniqueID;
			setUVDefaults();
		}

        /// Component callback functions
        virtual void addedRigidBody2D() { }
	private:
		void setUVDefaults()
		{
            if (m_Primitive2D == Primitive2D::Quad)
            {
			    m_UV.push_back(maths::vec2(0, 0));  // Bottom Left
			    m_UV.push_back(maths::vec2(0, 1));  // Top Left
                m_UV.push_back(maths::vec2(1, 1));  // Top Right
                m_UV.push_back(maths::vec2(1, 0));  // Bottom Right
            }
            else if (m_Primitive2D == Primitive2D::Triangle)
            {
                m_UV.clear();
				m_UV.push_back(maths::vec2(0, 0));      // Bottom Left
				m_UV.push_back(maths::vec2(0.5, 1));    // Top Middle
				m_UV.push_back(maths::vec2(1, 0));      // Bottom Right
            }
        }
        void GetRigidBody2DPosition()
        {
			for (int i = 0; i < components.size(); i++)
			{
                if (physics::RigidBody2D* rb = (dynamic_cast<physics::RigidBody2D*>(components[i])))
                {
                    m_Position = rb->GetPositionInPixels();
                }
                else
                    return;
			}
        }
        void GetRigidBody2DRotation()
        {
			for (int i = 0; i < components.size(); i++)
			{
				if (physics::RigidBody2D* rb = (dynamic_cast<physics::RigidBody2D*>(components[i])))
				{
					m_Rotation = rb->GetRotation();
				}
				else
					return;
			}
        }
    };

} }
 