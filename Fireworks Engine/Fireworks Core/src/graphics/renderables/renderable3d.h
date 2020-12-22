#pragma once

#include <vector>
#include <iostream>

#include "../shader.h"
#include "../buffers/buffer.h"
#include "../buffers/indexbuffer.h"
#include "../buffers/vertexarray.h"
#include "../../maths/maths.h"
#include "../texture.h"
#include "../renderer3d.h"

namespace fireworks { namespace graphics {

    struct VertexData3D
    {
        maths::vec3 vertex;
        maths::vec2 uv;
        float       tid;
        maths::vec4 color;
    };

    struct Transform
    {
        maths::vec3 position;
        maths::vec3 rotation;
        maths::vec3 scale;

        Transform(maths::vec3 pos = maths::vec3(0, 0, 0), maths::vec3 rot = maths::vec3(0, 0, 0), maths::vec3 scale = maths::vec3(1, 1, 1))
            : position(pos), rotation(rot), scale(scale)
        {
        }
    };

    enum class Primitive3D
    {
        Plane,
        Cube,
        UVSphere,   /* UV sphere procedurally generated using rings count on the CPU side */
        Torus,       /* UV Torus procedurally generated using preferences on the CPU side */
        None        /* If the primitive is none, then use the 3D Model for rendering the renderable*/
    };


    class Renderable3D
    {
    public:
        std::uint32_t                       objectID;
        Shader*                             shader;
    protected:
        Transform                           m_Transform;
        maths::vec4                         m_Color;
        Primitive3D                         m_Primitive3D;
        mutable std::vector<maths::vec2>    m_UV;
        Texture*                            m_Texture;
    private:
        static std::uint32_t                m_UniqueID;
    public:
    
        Renderable3D(Transform transform, maths::vec4 color, Primitive3D primitive3d)
            : m_Transform(transform), m_Color(color), m_Primitive3D(primitive3d), shader(nullptr), m_Texture(nullptr)
        {
            objectID = ++m_UniqueID;
            setUVDefaults();
        }

        Renderable3D(Transform transform, maths::vec4 color, Primitive3D primitive3d, Shader* shader)
            : m_Transform(transform), m_Color(color), m_Primitive3D(primitive3d), shader(shader), m_Texture(nullptr)
        {
            objectID = ++m_UniqueID;
            setUVDefaults();
        }

        Renderable3D(Transform transform, maths::vec4 color, Primitive3D primitive3d, Shader* shader, Texture* texture)
            : m_Transform(transform), m_Color(color), m_Primitive3D(primitive3d), shader(shader), m_Texture(texture)
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

        Renderable3D() : m_Texture(nullptr)
        {
            objectID = ++m_UniqueID;
        }

        virtual ~Renderable3D() { }

        virtual void submit(Renderer3D* renderer) const
        {
            renderer->submit(this);
        }

        inline const Transform& getTransform() const { return m_Transform; }
        inline const maths::vec4& getColor() const { return m_Color; }
        inline const std::vector<maths::vec2>& getUV() const { return m_UV; }
        inline const GLuint getTID() const { return m_Texture == nullptr ? 0 : m_Texture->getID(); }
        inline const Primitive3D& gerPrimitive() const { return m_Primitive3D; }

    private:
        void setUVDefaults()
        {
            int faces;
            if (m_Primitive3D == Primitive3D::Plane) /* Same as a Sprite */
            {
                faces = 1;
                // Iterating over each face
                for (int i = 0; i < faces; i++)
                {
                    m_UV.push_back(maths::vec2(0, 0));  // Bottom Left
                    m_UV.push_back(maths::vec2(0, 4));  // Top Left
                    m_UV.push_back(maths::vec2(4, 4));  // Top Right
                    m_UV.push_back(maths::vec2(4, 0));  // Bottom Right
                }
            }
            else if(m_Primitive3D == Primitive3D::Cube)
            {
                faces = 6;
                // Iterating over each face
                for (int i = 0; i < faces; i++)
                {
                    // Clockwise UV coordinates for each face
                    m_UV.push_back(maths::vec2(0, 0));  // Bottom Left
                    m_UV.push_back(maths::vec2(0, 1));  // Top Left
                    m_UV.push_back(maths::vec2(1, 1));  // Top Right
                    m_UV.push_back(maths::vec2(1, 0));  // Bottom Right
                }
            }
        }
    };

} }
